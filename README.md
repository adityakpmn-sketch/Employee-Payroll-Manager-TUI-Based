# Employee Payroll Management System

A Terminal-based User Interface (TUI) application written in C for managing employee records, tracking attendance, and calculating net salaries and performance bonuses.

---

## Table of Contents
- [Features](#features)
- [Project Structure](#project-structure)
- [ID Validation & Tier System](#id-validation--tier-system)
- [Salary & Bonus Logic](#salary--bonus-logic)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Compilation](#compilation)
  - [Execution](#execution)
- [Usage Guide](#usage-guide)
- [Future Improvements](#future-improvements)

---

## Features

- **Interactive Menu UI**: Clean text-based menu for seamless navigation.
- **Employee Onboarding**: Add new employees with automatic validation for ID formats and duplicate prevention.
- **Dynamic Tier Assignment**: Base salary and paid leaves are automatically determined based on ID codes.
- **Attendance & Salary Calculation**: Computes final salary based on total working days, actual days worked, and eligible leave days.
- **Bonus Engine**: Dynamically calculates variable bonuses based on employee work performance.
- **Employee Directory**: Displays stored employee records including names, IDs, and base salaries.

---

## Project Structure

```
.
├── main.c        # Core application source code
└── README.md     # Project documentation
```

### Data Structures (`struct Employee`)
| Field | Type | Description |
| :--- | :--- | :--- |
| `name` | `char[100]` | Employee's full name |
| `id` | `char[10]` | Unique employee identifier |
| `salary` | `float` | Base salary |
| `bonus` | `float` | Calculated bonus percentage |
| `workingdays` | `int` | Days worked by the employee |
| `paidleaves` | `int` | Annual allocated paid leaves |
| `sickleaves` | `int` | Annual allocated sick leaves |

---

## ID Validation & Tier System

Employee IDs determine job tiers, base pay, and paid leave allocations. The structure requires a valid prefix and sub-code:

| ID Sub-Code (`id[3..4]`) | Tier Level | Base Salary | Paid Leaves | Sick Leaves |
| :--- | :--- | :--- | :--- | :--- |
| `00` | Executive / Senior | 100,000 | 25 days | 12 days |
| `01` | Mid-Level | 10,000 | 20 days | 12 days |
| `02` | Junior / Entry | 1,000 | 12 days | 12 days |

*Note: IDs starting with prefix `STR` are flagged as invalid during entry.*

---

## Salary & Bonus Logic

1. **Adjusted Standard Days**:
   $$\text{Adjusted Days} = \text{Total Days} - (\text{Paid Leaves} + \text{Sick Leaves})$$

2. **Pro-rated Base Salary**:
   $$\text{Final Base} = \left( \frac{\text{Working Days}}{\text{Adjusted Days}} \right) \times \text{Base Salary}$$

3. **Bonus Calculation**:
   - Evaluated dynamically against actual working performance relative to target expectations.
   - Outputs final salary incorporating calculated bonus percentage:
     $$\text{Final Salary} = \text{Base Salary} \times \left(1 + \frac{\text{Bonus Percentage}}{100}\right)$$

---

## Getting Started

### Prerequisites
- A C compiler (GCC, Clang, or MSVC)
- Linux/macOS terminal or Windows command prompt/PowerShell

### Compilation
Using **GCC**:
```bash
gcc -o payroll main.c
```

### Execution
Run the compiled binary:

**Linux / macOS:**
```bash
./payroll
```

**Windows:**
```cmd
payroll.exe
```

---

## Usage Guide

Upon launching the application, you will see the main menu options:

```
==========================================================
                      Menu                        
==========================================================
  1. n -> New Employee
  2. l -> List Employee
  3. s -> Enter Salaries
  4. c -> Clear whole screen
  5. q -> quit application
Enter an Option : 
```

1. **`n` (New Employee)**: Prompt to register a new employee. Input name and ID.
2. **`l` (List Employee)**: Displays all onboarded employees with their base details.
3. **`s` (Enter Salaries)**: Runs salary calculation for all registered employees based on total period working days vs. days worked.
4. **`c` (Clear Screen)**: Resets the terminal screen view.
5. **`q` (Quit)**: Exits the application.

---
