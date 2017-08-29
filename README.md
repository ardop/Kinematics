# Motor Control

ARDOP uses the PCA9685 I2C driver for controlling its servo motors. Jetson drivers for the PCA are used.
Install the driver using steps mentioned here: (http://www.jetsonhacks.com/2015/10/14/pwm-servo-driver-board-nvidia-jetson-tk1/).

# Kinematics

The ARMA library is used for all matrix and vector operations.

Analytical and iterative inverse Kinematics solutions have been implemented.
1. Build the program by running `make` in the `./src` folder. 
2. Run the program using `sudo ./build/jac`
