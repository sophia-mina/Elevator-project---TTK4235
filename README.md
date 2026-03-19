# Elevatorproject 
This project simulates an elevator system and was developed as a partner project in the course [TTK4235 - Embedded Systems at NTNU](https://github.com/ITK-TTK4235). The simulator used in this project is available here: [Elevator Simulator](https://github.com/ITK-TTK4235/elevator_simulator). My partner, [natvo05](https://github.com/natvo05), and I implemented the logic in `main.c` and in the `c_files` and `header` directories, enabling the elevator to handle and execute orders from both internal and external buttons.

## How to run the simulation:
All commands must be run from the `skeleton_project` directory.

```bash
chmod +x SimElevatorServer   # only needed once
./SimElevatorServer          # start simulator

make                         # run in a new terminal
./elevator                   # start the elevator
```
## Simulator Interface

The simulator provides a visual representation of the elevator state directly in the terminal.

### Elevator position and movement

The elevator’s position is shown using the `#` symbol:
- `#>` → elevator moving up  
- `<#` → elevator moving down  
- `#`  → elevator stationary at a floor  

### Button indicators

Each floor displays button states:
- `*` = button is active (order registered)  
- `-` = button is inactive  

These indicators appear next to each floor and reflect both hall and cab orders.

### Floor indicator

The current floor is shown alongside the elevator symbol when it is aligned with a floor.

### State counter

A number displayed at the bottom of the simulator shows how many times the elevator has changed state (e.g., moving, stopping, door opening/closing).


### Controls

Use the following keys in the `./SimElevator` terminal:

- Hall up: `q w e`
- Hall down: `s d f`
- Cab: `z x c v`
- Obstruction: `-`
- Stop button: `p`


## More about the elevator

This project simulates the behaviour of a real elevator system, based on the specifications from the TTK4235 lab assignment.

### System overview

The elevator system consists of:
- A moving elevator car
- Floor sensors for detecting position
- Buttons for hall calls (up/down) and cab orders
- Indicator lights for orders and the current floor
- A motor controlling direction and movement

The system is designed to behave like a real elevator, including handling orders, movement logic, and safety constraints.

---

### Initialization

At startup, the elevator must enter a defined state, meaning it knows its current floor.

- If the position is unknown, the elevator moves until it reaches a valid floor
- All orders are ignored until initialisation is complete

---

### Order handling

The elevator follows these principles:

- All orders must eventually be served
- Orders in the current travel direction are prioritised
- The elevator does not stop for hall calls in the opposite direction while moving
- When stopping at a floor, all orders for that floor are cleared
- If no orders exist, the elevator remains idle

---

### Door behaviour

- The door opens when the elevator stops at the requested floor
- It remains open for ~3 seconds before closing
- If the stop button is pressed, the door opens and stays open while active
- If obstruction is detected, the door remains open until cleared

---

### Lights and indicators

- Button lights turn ON when an order is registered
- Lights turn OFF when the order is completed
- Only one floor indicator is active at a time
- The last passed floor is shown when moving between floors

---

### Safety features

The system includes several safety mechanisms:

- The elevator never moves while the door is open
- The door only opens when aligned with the floor
- Movement is restricted within valid floor limits
- Pressing the stop button:
  - Immediately stops the elevator
  - Clears all active orders
  - Ignores new inputs while active

---

### Robustness

- The system should not crash or require a restart during normal operation
- After initialisation, the elevator always knows its position
- Obstruction signals only affect the system when the door is open

---

### Implementation approach

The system is implemented using:
- A state machine (IDLE, MOVING, DOOR_OPEN, EMERGENCY_STOP)
- A queue system in the form of a linked list for managing orders
- Modular design separating logic, hardware interface, and control
