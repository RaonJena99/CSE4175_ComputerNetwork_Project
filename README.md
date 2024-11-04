# CSE4175_ComputerNetwork_Project

Here is a detailed `README.md` for both projects in English.

---

# Project: Computer Networks Assignments

This repository contains two major network assignments: **CRC Error Detection System** and **Routing Protocol Simulation**. Each project has been designed to meet specified requirements and can be executed from the command line.

## 1. Cyclic Redundancy Check (CRC) Error Detection

This project implements error detection using Cyclic Redundancy Check (CRC). CRC is a method used to detect errors in data transmission. This system consists of two main programs.

### File List
- `crc_encoder.cc`: Encodes a data file with CRC to detect errors
- `crc_decoder.cc`: Decodes an encoded file and detects any errors in transmission

### Usage

#### 1. crc_encoder
`crc_encoder` encodes an input file with CRC and outputs an encoded file.

```bash
./crc_encoder input_file output_file generator dataword_size
```

- `input_file`: Original data file
- `output_file`: Encoded file
- `generator`: CRC generator
- `dataword_size`: Size of the data unit (supports only 4 or 8 bits)

**Example**:
```bash
./crc_encoder datastream.tx codedstream.tx 1101 4
```

#### 2. crc_decoder
`crc_decoder` decodes an encoded file and detects errors, restoring the original data.

```bash
./crc_decoder input_file output_file result_file generator dataword_size
```

- `input_file`: Encoded data file
- `output_file`: Decoded data file after error detection
- `result_file`: Records the total and erroneous frames
- `generator`: CRC generator
- `dataword_size`: Size of the data unit (supports only 4 or 8 bits)

**Example**:
```bash
./crc_decoder codedstream.rx datastream.rx result.txt 1101 4
```

### Operation
1. **crc_encoder**:
   - Reads the input file and divides it into blocks of `dataword_size`.
   - For each block, performs modulo-2 division using the provided generator to generate CRC and produces a codeword, which is written to the output file.
   - Adds padding bits as necessary to align data with byte boundaries and records the number of padding bits in the first byte of the output file.

2. **crc_decoder**:
   - Reads the first byte of the input file to determine padding bits, and removes these bits to restore original data units.
   - Checks each codeword using the CRC generator to detect errors.
   - Records the total number of codewords and erroneous codewords in `result_file`.

### Error Handling
- Incorrect arguments: `usage: ./crc_encoder input_file output_file generator dataword_size`
- File open error: `input file open error` or `output file open error`

---

## 2. Routing Protocols Simulation

This project implements **Distance Vector** and **Link State** routing algorithms to create and update routing tables based on network topology changes.

### File List
- `distvec.cc`: Program that implements the Distance Vector routing algorithm
- `linkstate.cc`: Program that implements the Link State routing algorithm

### Usage

#### 1. linkstate
The `linkstate` program manages and updates routing tables using the Link State algorithm.

```bash
./linkstate topologyfile messagesfile changesfile
```

#### 2. distvec
The `distvec` program manages and updates routing tables using the Distance Vector algorithm.

```bash
./distvec topologyfile messagesfile changesfile
```

- `topologyfile`: File defining network topology
- `messagesfile`: File defining network messages
- `changesfile`: File defining network state changes

**Example**:
```bash
./linkstate topology.txt messages.txt changes.txt
./distvec topology.txt messages.txt changes.txt
```

### File Formats
1. **topologyfile**:
   - First line specifies the number of nodes.
   - Each subsequent line specifies a link between nodes and the cost.
   - Example:
     ```
     5
     0 1 8
     1 2 3
     ```

2. **messagesfile**:
   - Each line defines a message with source node, destination node, and message content.
   - Example:
     ```
     1 0 here is a message from 1 to 0
     2 4 this one gets sent from 2 to 4!
     ```

3. **changesfile**:
   - Each line specifies a change in link cost between nodes, where `-999` indicates the link is removed.
   - Example:
     ```
     1 3 1
     1 3 -999
     ```

### Operation
1. **Initial Network Setup**:
   - Reads `topologyfile` to initialize network topology and builds routing tables for each node.
   - Uses `messagesfile` to simulate message routing from source to destination nodes through the routing table.

2. **Network State Changes**:
   - Sequentially applies changes in `changesfile` and updates the routing tables.
   - Recalculates and simulates message routing after each change.

### Output Format
- Routing tables and message delivery paths are saved to `output_dv.txt` (Distance Vector) and `output_ls.txt` (Link State).
- If no path exists from sender to receiver, outputs `cost infinite` and `unreachable`.

### Error Handling
- Incorrect arguments: `usage: linkstate topologyfile messagesfile changesfile`
- File open error: `Error: open input file`

---

After each program completes, review the output files to validate routing tables and message delivery paths.
