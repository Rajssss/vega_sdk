# MDP SDK

The MDP SDK contains the following peripherals,example programs for baremetal development

### Peripherals
- UART
- PLIC
- SPI
- GPIO

### Example programs
- Hello world 

## Quick Start

> For Ubuntu 18.04 (or newer) install below listed packages.

- MDP-TOOLS [git clone http://10.176.19.212:3000/MDP/mdp-tools]
-

Clone the repository

### Creating Workspace

This needs to be done every time you want a clean setup based on the latest layers.

```bash
git clone http://10.176.19.212:3000/MDP/mdp-sdk
cd mdp-sdk
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

## License
[MIT](https://opensource.org/licenses/MIT)