import os
import sys
import re
import shutil
import subprocess

CSS_FILE_PATH = "_variables-dusk.scss"

SVG_TEMPLATE_EXTENSION = ".ink.svg"
SVG_TARGET_EXTENSION = ".svg"
CSS_TEMPLATE_EXTENSION = ".ink.css"
CSS_TARGET_EXTENSION = ".css"
RCC_EXCLUDED_EXTENSIONS = ['.ink.svg', '.ink.css', '.py', '.scss', '.qrc', '.ui']

TARGET_THEME_DIR = "."
THEME_NAME = os.path.basename(os.getcwd())
COLOR_PAIRS = []

# Lists all .scss files in the current directory
def list_scss_files():
  return [f for f in os.listdir('.') if f.endswith('.scss')]

# Prompts the user to select a file from a list
def prompt_user_to_select_file(files):
  print("Multiple SCSS files detected. Please choose one:")
  for idx, file in enumerate(files, 1):
    print(f"{idx}: {file}")
  while True:
    try:
      choice = int(input("Enter the number of your choice: ")) - 1
      if 0 <= choice < len(files):
        return files[choice]
    except ValueError:
      pass
    print("Invalid choice. Please enter a number from the list.")

# Validates the CSS_FILE_PATH or lists files for selection
def validate_css_file():
  global CSS_FILE_PATH
  if not os.path.exists(CSS_FILE_PATH):
    print(f"Specified file '{CSS_FILE_PATH}' does not exist.")
    scss_files = list_scss_files()
    if not scss_files:
      print("No .scss files found in the current directory. Exiting.")
      sys.exit(1)
    elif len(scss_files) == 1:
      CSS_FILE_PATH = scss_files[0]
    else:
      CSS_FILE_PATH = prompt_user_to_select_file(scss_files)
  return CSS_FILE_PATH

# Function to parse the scss file and generate color pairs with property and color
def generate_color_pairs_from_styling_file():
  try:
    with open(CSS_FILE_PATH, 'r') as file:
      for line in file:
        # Use regular expressions to extract property names and RGB/RGBA values
        match = re.search(r'--(.*?): (rgba?\(\d+, \d+, \d+(?:, ?\d*(?:\.\d+)?)?\));', line)

        if match:
          property_name = match.group(1)
          color_value = match.group(2)

          # Extract the RGB/RGBA values from the color value
          rgba_match = re.match(r'(rgba?)\((\d+), (\d+), (\d+)(?:, ?(\d*(?:\.\d+)?|\.\d+))?\)', color_value)
          color_format = rgba_match.group(1)
          red = int(rgba_match.group(2))
          green = int(rgba_match.group(3))
          blue = int(rgba_match.group(4))
          alpha = float(rgba_match.group(5)) if rgba_match.group(5) else 1.0

          # Convert the RGB/RGBA values to hex format
          hex_color = f"#{red:02X}{green:02X}{blue:02X}"

          if color_format == 'rgba':
            hex_color += f"{int(alpha * 255):02X}"

          # Append the property name and hex color as a pair to the list
          COLOR_PAIRS.append((property_name.strip(), hex_color))

  except FileNotFoundError:
    print(f"File '{CSS_FILE_PATH}' not found.")
  except Exception as e:
    print(f"An error occurred: {str(e)}")

# Function to write the RCC file
def write_resource_file(file_list):
  with open(output_file, 'w') as f:
    qresource_string = f' <qresource prefix="/themes/{THEME_NAME}">\n'
    f.write('<RCC>\n')
    f.write(qresource_string)
    for file_path in file_list:
      f.write(f'  <file>{file_path}</file>\n')
    f.write(' </qresource>\n')
    f.write('</RCC>\n')

# Function to find and collect file paths
def find_files_and_create_resource_file(directory):
  file_list = []
  for root, dirs, files in os.walk(directory):
    for file in files:
      if not any(file.endswith(ext) for ext in excluded_extensions):
        file_list.append(os.path.relpath(os.path.join(root, file), directory))
  write_resource_file(file_list)

# Function to optimize the SVG file using scour
def execute_scour(file_path):
  temporary_file = file_path + ".tmp"
  command = [
    "scour",
    "-i", file_path,
    "-o", temporary_file,
    "--disable-group-collapsing",
    "--disable-simplify-colors",
  ]
  try:
    subprocess.run(command, check=True)
    os.replace(temporary_file, file_path)
  except subprocess.CalledProcessError as e:
    print(f"An error occurred: {str(e)}")
  except FileNotFoundError:
    print("scour command not found. Please ensure scour is installed and in your system's PATH.")

# Function to convert rgba hex to argb
def convert_rgba_to_argb(input_string):
  if input_string.startswith("#") and len(input_string) == 9:
    aa = input_string[-2:]
    rrggbb = input_string[1:-2]
    return "#" + aa + rrggbb
  else:
    return input_string

# Function that converts alpha decimal to hex and adds it to a hex color
def hex_to_rgba(hex_color, alpha):
  hex_color = hex_color.lstrip('#')
  r = int(hex_color[0:2], 16)
  g = int(hex_color[2:4], 16)
  b = int(hex_color[4:6], 16)
  alpha = max(0.0, min(1.0, alpha))
  rgba_string = f'rgba({r},{g},{b},{alpha:.1f})'
  return rgba_string

# Function that gets a color from the global color list by name
def get_color_by_name(color_name, alpha):
  for pair in COLOR_PAIRS:
    if pair[0] == color_name:
      hex_color = pair[1]
      return hex_to_rgba(hex_color, alpha)

  print(f"The color was not found: {color_name}")
  return None

# Function that extracts the last two characters of a hex color and converts it to a decimal
def calculate_opacity(hex_color):
  opacity_hex = hex_color[-2:]
  opacity_decimal = int(opacity_hex, 16) / 255.0
  return f'"{opacity_decimal:.3f}"'

# Function that creates a theme svg file based on a template file
def create_theme_svg(source_svg_file, target_svg_file):
  with open(source_svg_file, 'r') as input_file, open(target_svg_file, 'w') as output_file:
    try:
      file_content = input_file.read()
      color_dict = {property_name: color for property_name, color in COLOR_PAIRS}

      # Define a regular expression pattern to match "fill="url(#PROPERTY)" and "stroke="url(#PROPERTY)"
      pattern = r'((fill|stroke))="url\(#(' + '|'.join(re.escape(property_name) for property_name in color_dict.keys()) + r')\)"'

      replacements_count = [0]

      def replacement_callback(match):
        replacements_count[0] += 1
        return (
          f'{match.group(1)}="{color_dict[match.group(3)][:7]}" '
          f'{"fill-opacity=" if len(color_dict[match.group(3)]) == 9 and match.group(2) == "fill" else ""}'
          f'{"stroke-opacity=" if len(color_dict[match.group(3)]) == 9 and match.group(2) == "stroke" else ""}'
          f'{calculate_opacity(color_dict[match.group(3)]) if len(color_dict[match.group(3)]) == 9 else ""}'
        )

      replaced_content = re.sub(pattern, replacement_callback, file_content)

      if os.path.basename(target_svg_file) == "tabWidget.svg":
        replaced_content = replaced_content.replace('$(theme-name)', THEME_NAME)

      print(f"Created SVG file {target_svg_file} with {str(replacements_count[0])} replacements.")
      output_file.write(replaced_content)
      output_file.close()
      execute_scour(target_svg_file)

    except FileNotFoundError:
      print(f"File '{source_svg_file}' not found.")
    except Exception as e:
      print(f"An error occurred: {str(e)}")

# Function that creates a theme CSS file based on a template file
def create_theme_css(source_file, target_file):
  with open(source_file, 'r') as input_file, open(target_file, 'w') as output_file:
    try:
      file_content = input_file.read()

      for pair in COLOR_PAIRS:
        property_name, color = pair
        file_content = file_content.replace('--' + property_name, convert_rgba_to_argb(color))

      if os.path.basename(target_file) == "overlay.css":
        file_content = file_content.replace('$(overlay-color)', get_color_by_name("container-background-color", 0.8))

      output_file.write(file_content)
      print(f"Created CSS file {target_file}.")

    except FileNotFoundError:
      print(f"File '{source_file}' not found.")
    except Exception as e:
      print(f"An error occurred: {str(e)}")

# Function to write the resource file
def write_resource_file(file_list):
  output_file = f'{THEME_NAME}.qrc'
  with open(output_file, 'w') as f:
    try:
      qresource_string = f' <qresource prefix="/themes/{THEME_NAME}">\n'
      f.write('<RCC>\n')
      f.write(qresource_string)
      for file_path in file_list:
        f.write(f'  <file>{file_path}</file>\n')
      f.write(' </qresource>\n')
      f.write('</RCC>\n')
      print(f'Created RCC file {output_file}')
    except Exception as e:
      print(f"An error occurred: {str(e)}")

# Function to find and collect file paths and write the resource file
def find_files_and_create_resource_file(directory):
  file_list = []
  for root, dirs, files in os.walk(directory):
    for file in files:
      if not any(file.endswith(ext) for ext in RCC_EXCLUDED_EXTENSIONS):
        file_list.append(os.path.relpath(os.path.join(root, file), directory))
  write_resource_file(file_list)

# Function that renames theme template files
def rename_file(current_file_name, new_file_name):
  if os.path.exists(current_file_name) and not os.path.exists(new_file_name):
    try:
      os.rename(current_file_name, new_file_name)
      print(f"Renamed '{current_file_name}' to '{new_file_name}' - remember to update for the new theme!")
    except Exception as e:
      print(f"An error occurred: {str(e)}")
  elif os.path.exists(new_file_name):
    print(f"File '{new_file_name}' already exists - make sure it is updated for the new theme!")
  else:
      print(f"Make sure that the theme includes '{new_file_name}'!")

# Function that creates a theme
def create_theme(full_theme=True):
  CSS_FILE_PATH = validate_css_file()
  print(f"Using SCSS file: {CSS_FILE_PATH}")

  generate_color_pairs_from_styling_file()
  for root, dirs, files in os.walk(TARGET_THEME_DIR):
    for file in files:
      if file.endswith(SVG_TEMPLATE_EXTENSION):
        file_path = os.path.join(root, file)
        create_theme_svg(file_path, file_path[:-len(SVG_TEMPLATE_EXTENSION)] + SVG_TARGET_EXTENSION)
      elif file.endswith(CSS_TEMPLATE_EXTENSION):
        file_path = os.path.join(root, file)
        create_theme_css(file_path, file_path[:-len(CSS_TEMPLATE_EXTENSION)] + CSS_TARGET_EXTENSION)
  if full_theme:
    rename_file("openbridge5_day.ui", f"{THEME_NAME}.ui")
    rename_file("openbridge5_day.png", f"{THEME_NAME}.png")
    find_files_and_create_resource_file(TARGET_THEME_DIR)

# Function that deletes files by extension
def delete_files_by_extension(dir_path, file_extension):
  for root, _, files in os.walk(dir_path):
    for file in files:
      if file.endswith(file_extension):
        file_path = os.path.join(root, file)
        os.remove(file_path)
        print(f"Deleted: {file_path}")

# Function for printing usage guidelines
def print_help():
  print("Follow these steps to create a new theme using create-theme.py:")
  print(f" 1. Copy the openbridge5_day theme directory and rename it to your theme name (currently named '{THEME_NAME}').")
  print(f" 2. Provide an SCSS file with colors and edit CSS_FILE_PATH accordingly (currently set to '{CSS_FILE_PATH}').")
  print(f" 3. Execute the script with 'python3 {os.path.basename(__file__)} run'.")
  print(f" 4. Execute the script with 'python3 {os.path.basename(__file__)} clean' to remove the template files.")

def autorun():
  from watchdog.observers import Observer
  from watchdog.events import FileSystemEventHandler
  import time

  class MyHandler(FileSystemEventHandler):
    file_cache = {}
    def on_modified(self, event):
        if not event.is_directory and event.src_path.endswith(".ink.svg") and not event.src_path in self.file_cache:
            self.file_cache[event.src_path] = time.time()
            create_theme()

    def update_file_cache(self):
      drop_files = []
      for file in self.file_cache:
        if time.time() - self.file_cache[file] > 1:
          drop_files.append(file)
          
      for file in drop_files:
        self.file_cache.pop(file)

  # Create observer and event handler
  observer = Observer()
  event_handler = MyHandler()

  # Set up observer to watch a specific directory
  directory_to_watch = "."
  observer.schedule(event_handler, directory_to_watch, recursive=True)

  # Start the observer
  observer.start()

  # Keep the script running
  try:
      while True:
          event_handler.update_file_cache()
  except KeyboardInterrupt:
      observer.stop()

  observer.join()

if len(sys.argv) > 1:
  if sys.argv[1] == 'clean':
    delete_files_by_extension(TARGET_THEME_DIR, SVG_TEMPLATE_EXTENSION)
    delete_files_by_extension(TARGET_THEME_DIR, CSS_TEMPLATE_EXTENSION)
  elif sys.argv[1] == 'run':
    create_theme()
  elif sys.argv[1] == 'files':
    create_theme(False)
  elif sys.argv[1] == 'autorun':
    autorun()
  else:
    print_help()
else:
  print_help()
