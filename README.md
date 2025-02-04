# Parking-Management-System

A C-based Parking Management System that automates vehicle parking operations for small to medium-sized facilities. It efficiently allocates parking slots, calculates parking fees based on duration, and enables vehicle search by registration number. Designed for malls and office buildings, the system is stable, user-friendly, and expandable with features like automated billing and a GUI.

# Important Libraries

The Parking Management System is implemented in C and utilizes the following standard libraries:

1. `stdio.h` : Provides input and output functions for interacting with users.

2. `stdlib.h` : Supports memory allocation and utility functions.

3. `string.h` : Enables string manipulation, such as searching and comparison.

4. `time.h` : Used to calculate parking duration and timestamps.

5. `stdbool.h` (if needed) : Supports boolean data types for better readability.

# Highlights

1. `Automated Slot Allocation`: Efficiently assigns parking slots and updates records.

2. `Real-time Fee Calculation`: Computes parking charges based on duration.

3. `Persistent Data Storage`: Saves and retrieves vehicle data from a file (parking.txt).

4. `Vehicle Search Functionality`: Quickly finds parked vehicles using registration numbers.

5. `User-friendly CLI Interface`: Simple and intuitive console-based operation.

6. `Scalability`: Supports up to 100 vehicles and can be expanded further.

# Requirements
GCC Compiler 9.3.0 or Later

VS Code

MinGW (For Windows users, to compile and run C programs)

`stdio.h` (For standard input/output operations)

`stdlib.h` (For memory allocation and utility functions)

`string.h` (For handling string operations)

`time.h` (For tracking vehicle parking duration and calculations)

# Implementation & Testing

The system is implemented in C with standard file handling for data persistence. Key functionalities such as data loading, slot allocation, and fee calculation are tested under various scenarios, including:

Normal Operations: Vehicle parking, searching, and retrieval.

Edge Cases: Full parking lot handling.

Fee Calculation Accuracy: Validation of charges based on different parking durations.

# Future Enhancements

Graphical User Interface (GUI): For improved user experience.

Automated Billing System Integration: For seamless payment processing.

# About Me
Hello! I am Kinshuk, an Engineering student at Kalinga Institute of Industrial Technology. This project is now open-source, and I welcome contributions. Feel free to fork the repository, submit pull requests, and support my work!
