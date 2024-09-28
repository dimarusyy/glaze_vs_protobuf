python -m venv .venv
.\.venv\Scripts\pip.exe install -r requirements.txt
.\.venv\Scripts\conan.exe install . --output-folder=. --update --build=missing --settings=build_type=Debug --profile:all=.\conanprofile-debug.txt
