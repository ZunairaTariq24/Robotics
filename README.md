# Robotic Arm Bot

A student-friendly, robotics project featuring a mobile robotic platform equipped with a 2-servo motorized arm. This project was developed as an educational exercise in basic robotics, circuit design, and mechanical integration.

## Project Overview
This bot is designed for simplicity and functionality, utilizing a two-servo configuration to perform basic pick-and-place tasks. It serves as an accessible entry point for students interested in hardware-software integration.

## Technical Specifications
- **Controller:** Arduino-based (or compatible microcontroller)
- **Actuation:** 2x Servo Motors
- **Chassis:** Custom student-built platform
- **Power:** Battery-operated for mobility
- **Bluetooth control Module** L239 D

## Features
- **Simplified Design:** Utilizes only 2 servos for cost-effectiveness and reduced circuit complexity.
- **Compact Build:** Small form factor suitable for desk-top prototyping and testing.
- **Educational Value:** Ideal for learning the basics of PWM control, structural assembly, and basic automation logic.

## Getting Started
### Prerequisites
- Arduino IDE installed.
- Basic understanding of servo motor control (PWM).

### Wiring
- **Servo 1 (Base/Joint):** 
- **Servo 2 (Gripper/Arm):** 

### Software
1. Clone this repository.
2. Open the `robot_arm_control.ino` file in the Arduino IDE.
3. Upload the code to your microcontroller.
4. Ensure your power supply is adequate for the two servos to prevent resets.

## Future Improvements
- Implement a more robust base for better stability.
- Add sensor integration (e.g., ultrasonic or IR) for obstacle avoidance.
- Enhance the grip mechanism for better payload handling.

## License
This project is open-source and available for educational use.
