# Vega SDK

The Vega SDK contains the following peripheral APIs, example programs for baremetal development.
### Peripheral APIs
- UART
- PLIC
- SPI
- GPIO
- TIMER

### Example programs
- Hello world 

## Quick Start

> For Ubuntu 18.04 (or newer) install below listed packages.

- Vega-Tools [git clone https://gitlab.com/cdac-vega/vega-tools.git]
- build-essential
- git

### Creating Workspace

Clone the repository

```bash
git clone https://gitlab.com/cdac-vega/vega-sdk.git
cd vega-sdk
```

### Setting up Build Environment

```bash
./setup-env.sh
```
### Compile sample program

Please change the directory to sample program, example:

```bash
cd ./examples/uart/hello_world/
make clean
make
```

### Running on Hardware

Transfer the binary file to board.

## Documentation

[Vega SDK Documentation ](https://cdac-vega.gitlab.io/sdkuserguide.html)

## License
[MIT](https://opensource.org/licenses/MIT)
