# arc - AUR Helper

`arc` is a lightweight AUR (Arch User Repository) helper written in C++. It allows users to search for packages in the AUR and display the results in a user-friendly format.

## Table of Contents

- [arc - AUR Helper](#arc---aur-helper)
  - [Table of Contents](#table-of-contents)
  - [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Building the Project](#building-the-project)
  - [Usage](#usage)
  - [Cleaning Up](#cleaning-up)
  - [Contributing](#contributing)
  - [License](#license)

## Getting Started

### Prerequisites

Ensure you have the following installed:

- CMake (version 3.10 or higher)
- A C++ compiler (e.g., GCC)
- GNU Make
- cURL library
- JSON for Modern C++ library

On Arch Linux, you can install the dependencies using:

```sh
sudo pacman -S cmake gcc make curl nlohmann-json
```

### Building the Project

1. Clone the repository:

```sh
git clone <repository-url>
cd arc
```

2. Create a build directory and navigate into it:

```sh
mkdir build
cd build
```

3. Run CMake to configure the project:

```sh
cmake ..
```

4. Build the project using Make:

```sh
make
```

## Usage

To search for a package in the AUR, run the `arc` executable followed by your search query:

```sh
./arc <search_query>
```

Replace `<search_query>` with the name of the package you want to search for. The results will be displayed in the terminal.

## Cleaning Up

To clean up the build files, you can simply remove the `build` directory:

```sh
rm -rf build
```

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes. Ensure your code adheres to the project's coding standards and includes appropriate tests.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
