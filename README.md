# STM32_I2C_CAN

Implementation of I2C and CAN Communication using STM32.

---

## 📌 Goal

- Read acceleration data along the X, Y, Z axes from the accelerometer.
  - Display one axis value on a seven-segment display.
  - Log all axis values via UART (serial terminal).
- Receive CAN messages and:
  - Filter based on message ID.
  - Display data on seven-segment display, LEDs, or UART.
- Send CAN messages such as:
  - Switch states.
  - Counter values.

---

## 🔧 Hardware Requirements

- **STM32L562E-DK** development board  
- **LSM6DSO IMU Sensor**  
  - [Datasheet](https://www.st.com/resource/en/datasheet/lsm6dso.pdf)
- **Peripheral circuits**
  - Provided during university labs or [available online](http://tiny.cc/rfje001)

---

## 💻 Software Setup

### 1️⃣ Peripheral Configuration in STM32CubeIDE

#### ✅ I2C1 Configuration
- **Frequency**: 100 kHz

#### ✅ FDCAN1 Configuration
- **Kernel Clock Divider**: 1 (results in 110 MHz peripheral clock)
- **Frame Format**: Classic CAN
- **Mode**: Internal Loopback for testing (switch to Normal later)
- **Bit Timing Settings**:
  - Bitrate `fb = 250 kHz` → `Tbit = 1 / fb`
  - Typical bit time = 8–25 time quanta (Tq)
  - **Prescaler**: 22 → Tq = 1 / (fp / Prescaler) = 1 / (110 MHz / 22)
  - **Seg1 + Seg2**: Set so sample point is 70–90% of the bit time  
    _(Seg1 includes Sync segment of 1 Tq)_
  - **Sync Jump Width (SJW)**: 1 Tq
  - **Note**: Only configure nominal values; CAN-FD is not used in this lab.

---

### 2️⃣ IMU Sensor Communication (LSM6DSO)

- Abstraction Layer: `./core/App/lsm6dso.h`
- **Initialization**:
  - Use `LSM6DSO_Init()` to read device ID and configure control registers.
  - Confirms correct I2C communication.
- **Data Reading**:
  - Use `LSM6DSO_Update()` to read and scale:
    - Accelerometer (X, Y, Z)
    - Gyroscope (angular velocity)
  - Display selected axis on seven-segment.
  - Log all via UART.

---

### 3️⃣ CAN Communication

- Abstraction Layer: `./core/App/CanCommunication.h`

#### 🟢 Initialization
- Set filters to accept specific message IDs into FIFO0 or FIFO1.

#### 🟢 Transmission
- Use `CanCommunication_Send()` to broadcast message:
  - CanFD Frame: TxHeader, payload, data, etc. 

#### 🟢 Reception
- Use `CanCommunication_Receive()`:
  - Filter messages based on ID
  - Display values on 7-segment/LED/UART accordingly

---

## 📎 Notes
- Ensure byte order (endianness) is respected when communicating over I2C or CAN. In STM32, it use little endian.
- Device ID bits may be used in CAN messages to differentiate sources.

---
