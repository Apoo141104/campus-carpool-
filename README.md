# 🚗 Campus Carpool

Welcome to **Campus Carpool**, a C++ project designed to facilitate shared rides among campus users. This application enables users to register, log in, create and join rides, match carpool requests, and communicate with other users. It also includes features for reporting inappropriate behavior, ensuring a safe and efficient carpooling experience.

---

## 🧰 Features

- **User Registration & Authentication**: Secure sign-up and login functionalities.
- **Ride Management**: Create, view, and manage carpool rides with details like departure location, destination, and available seats.
- **Carpool Matching**: Efficiently match users based on their ride requests and preferences.
- **Communication**: In-app messaging system for users to coordinate rides.
- **Reporting System**: Report inappropriate behavior to maintain community standards.

---

## 🛠️ Components

- **Graph Class**: Manages geographic locations and connections for efficient distance calculations.
- **User Class**: Defines user profiles, including personal and ride-related information.
- **Ride Class**: Represents individual rides with pertinent details.
- **CarpoolRequest Class**: Handles user requests for carpools, encompassing location, date, time, and vehicle type.
- **CarpoolSystem Class**: Oversees the overall carpooling operations, integrating all components seamlessly.

---

## 💻 Getting Started

### Prerequisites

- A C++ compiler (e.g., GCC, Clang, or MSVC)
- A terminal or command-line interface

### Installation

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/Apoo141104/campus-carpool-.git
   cd campus-carpool-
   ```
2. **Compile the Application:**:
   ```bash
   g++ project.cpp -o campus_carpool
   ```
3. **Run the Application:**
   ```bash
   ./campus_carpool
   ```
