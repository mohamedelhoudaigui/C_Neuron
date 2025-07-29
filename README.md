C-Neuron 🧠

A simple, lightweight, and educational feedforward neural network built from scratch in C.

![alt text](https://img.shields.io/badge/Language-C-blue.svg)
![alt text](https://img.shields.io/badge/Standard-C11-brightgreen.svg)
![alt text](https://img.shields.io/badge/License-MIT-yellow.svg)

This project is an exploration into the fundamental concepts of neural networks, implemented with no external machine learning libraries. It's designed to be a clear and understandable guide to how networks learn through forward and backward propagation.

<br>

✨ Features

Dynamic Network Architecture: Easily configure the number of layers and neurons.

Activation Functions: Includes Sigmoid and ReLU activation functions.

Backpropagation: Full implementation of the backpropagation algorithm to train the network.

Smart Initialization: Uses Xavier/Glorot initialization for weights to improve training stability.

Custom Garbage Collector: A simple, centralized memory manager to prevent leaks.

Easy to Compile: Comes with a Makefile for one-command compilation.

Educational: Code is structured and commented to be a learning resource.

<br>

🔧 Getting Started

Getting the project up and running is as simple as cloning the repository and running make.

Prerequisites

You'll need a C compiler (like gcc or clang) and make installed on your system.

Compilation

Clone the repository:

```
git clone https://github.com/mohamedelhoudaigui/c_neuron_network.git
cd c_neuron_network
```


Compile the project:
Use the included Makefile to compile the source code. This will create an executable file named nn.

```
make
```
Running the Network

Execute the compiled program to start the training and testing process defined in src/main.c.

```
./nn
```

You will see the network train for a set number of epochs and then test its performance on new data, printing the average error.

<br>

🏗️ How It Works

The network follows the classic feedforward architecture. Data flows from the input layer, through the hidden layers, to the output layer.

Network Architecture

A simple visual representation of the data flow:

  [Input Layer]      [Hidden Layer(s)]      [Output Layer]
  ┌───────────┐      ┌───────────────┐      ┌────────────┐
  │  Node 1   │──────│    Node 1     │──────│   Node 1   │
  │   ...     │      │      ...      │      │    ...     │
  │  Node N   │──────│    Node M     │──────│   Node K   │
  └───────────┘      └───────────────┘      └────────────┘
       │                    │                      │
       └────────────────────┴──────────────────────┘
                    Forward Propagation ->

Training Loop

The network learns by iteratively adjusting its weights and biases to minimize error (in this case, Mean Squared Error).

Forward Propagation: Input data is fed to the network, and an output is computed by passing the results from one layer to the next.

Calculate Error: The network's output is compared to the true, expected output to calculate the error.

Backpropagation: The error is propagated backward through the network. The delta for each neuron is calculated, representing its contribution to the total error.

Update Weights & Biases: The weights and biases are adjusted using gradient descent based on the calculated deltas and a defined learning rate (L_RATE).

This cycle is repeated for a number of NUM_EPOCHS until the network's predictions improve.

<br>

📁 Project Structure

The project is organized into source files, headers, and a Makefile for clarity and scalability.

c_neuron_network/
├── Makefile                # Manages compilation
├── headers/                # Header files
│   ├── funcs.h             # Core neural network functions
│   ├── garbage.h           # Custom memory manager
│   ├── macro.h             # Project-wide constants and enums
│   ├── types.h             # Struct definitions (Node, Layer, NN)
│   └── utils.h             # Utility functions
└── src/                    # Source code
    ├── funcs.c             # Implementation of core functions
    ├── garbage.c           # Implementation of the garbage collector
    ├── main.c              # Main driver for training and testing
    └── utils.c             # Implementation of utility functions

<br>

🤝 Contributing

Contributions, issues, and feature requests are welcome! Feel free to check the issues page.

<br>

📜 License

This project is licensed under the MIT License. See the LICENSE file for details.
