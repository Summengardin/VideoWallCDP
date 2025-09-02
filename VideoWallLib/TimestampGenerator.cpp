#include "TimestampGenerator.h"

using namespace VideoWallLib;
/*!
  \class VideoWallLib::TimestampGenerator
  \inmodule VideoWallLib

  \section1 Usage

  Add documentation for TimestampGenerator here.
*/


/* --- Portable time utilities --- */
namespace time_utils {

    // Convert time_t -> local std::tm (thread-safe)
    inline std::tm to_local_tm(std::time_t t) {
        std::tm result{};
    #if defined(_WIN32)
        localtime_s(&result, &t);
    #else
        localtime_r(&t, &result);
    #endif
        return result;
    }

    // Convert time_t -> UTC std::tm (thread-safe)
    inline std::tm to_utc_tm(std::time_t t) {
        std::tm result{};
    #if defined(_WIN32)
        gmtime_s(&result, &t);
    #else
        gmtime_r(&t, &result);
    #endif
        return result;
    }

    // Normalize a timezone name (IANA -> POSIX if possible)
    inline std::string normalize_timezone(const std::string& tz) {
        if (tz.empty()) return tz;
        std::string mapped;
        if (tzmap_legacy::iana_to_posix(tz, mapped)) return mapped;
        return tz;
    }

    // RAII helper to temporarily set TZ environment variable
    class TemporaryTimezone {
        std::string previous_tz;
        bool had_previous;
    public:
        explicit TemporaryTimezone(const char* tz) {
        #if defined(_WIN32)
            char* prev = nullptr; size_t len = 0;
            _dupenv_s(&prev, &len, "TZ");
            had_previous = (prev != nullptr);
            if (had_previous) previous_tz.assign(prev, len ? len - 1 : 0);
            free(prev);

            if (tz && *tz) _putenv_s("TZ", tz); else _putenv_s("TZ", "");
            _tzset();
        #else
            const char* prev = std::getenv("TZ");
            had_previous = (prev != nullptr);
            if (had_previous) previous_tz = prev;

            if (tz && *tz) ::setenv("TZ", tz, 1); else ::unsetenv("TZ");
            ::tzset();
        #endif
        }

        ~TemporaryTimezone() {
        #if defined(_WIN32)
            if (had_previous) _putenv_s("TZ", previous_tz.c_str()); else _putenv_s("TZ", "");
            _tzset();
        #else
            if (had_previous) ::setenv("TZ", previous_tz.c_str(), 1); else ::unsetenv("TZ");
            ::tzset();
        #endif
        }
        };

    // Format std::tm into string
    inline std::string format_time(const std::tm& tm, const char* fmt) {
        std::ostringstream oss;
        oss << std::put_time(&tm, fmt);
        return oss.str();
    }

    // Format current time into string (UTC, local, or custom TZ)
    inline std::string formatted_now(const char* fmt, bool use_utc, const std::string& tz) {
        const std::time_t now = std::time(nullptr);

        if (use_utc) {
            return format_time(to_utc_tm(now), fmt);
        }

        const std::string tz_normalized = normalize_timezone(tz);

        if (!tz_normalized.empty()) {
            TemporaryTimezone guard(tz_normalized.c_str());
            return format_time(to_local_tm(now), fmt);
        }
        return format_time(to_local_tm(now), fmt);
    }

    // Parse bool from string
    inline bool parse_bool(const std::string& s) {
        return (s == "1" || s == "true" || s == "TRUE" || s == "True" ||
                s == "yes" || s == "YES" || s == "on" || s == "ON");
    }

} // namespace time_utils


/*!
  \internal
  \brief Component constructor. The first function to be called. Can be used to initialize member variables, etc.
*/
TimestampGenerator::TimestampGenerator()
{
}

/*!
  \internal
  \brief Component destructor. The last function to be called. Typically used to clean up when stopping, like freeing
  allocated memory, etc.
*/
TimestampGenerator::~TimestampGenerator()
{
}

/*!
  \internal
  \brief Creates the component instance and other related CDP objects. Called after constructor

  Note, that this function is normally filled automatically by the code generator.
*/
void TimestampGenerator::Create(const char* fullName)
{
    CDPComponent::Create(fullName);
    TimestampFormatted.Create("TimestampFormatted",this);
    Format.Create("Format",this);
    UTC.Create("UTC",this);
    TZ.Create("TZ",this);
}

/*!
  \internal
  \brief Creates a model instance for this class and fills model data. Registers messages, states and state transitions.

  Note, that this function is normally filled automatically by the code generator.
*/
void TimestampGenerator::CreateModel()
{
    CDPComponent::CreateModel();

    RegisterStateProcess("Null", (CDPCOMPONENT_STATEPROCESS) &TimestampGenerator::ProcessNull, "Initial Null state");
}

/*!
  \internal
  \brief Configures the component by reading the configuration. Called after Create()/CreateModel().

  Note, that this function is normally filled automatically by the code generator.
*/
void TimestampGenerator::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);
}

/*!
 \brief Component Null state processing function

 Write your component's processing code here. When the component is simple, all the processing code may reside here.
 This function gets called periodically. The period is changed by setting the "fs" (frequency) Property when you use
 the component in a project.
 Functions called ProcessSTATENAME(), like ProcessNull(), are state processing functions and are only called when
 components are in given state. The default component state is "Null".
 Note, that state processing functions are not allowed to block (i.e. read files, sleep, communicate with network in
 blocking mode etc.) For blocking code use the 'Threaded Component Model' wizard instead.

 Please consult CDP Studio "Code Mode Manual" for more information and examples.
*/
void TimestampGenerator::ProcessNull()
{
    TimestampFormatted = time_utils::formatted_now(std::string(Format).c_str(), UTC, TZ);
}
