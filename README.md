# Philosophers 🧵🍝
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)

## 📌 Description

This project is part of the 42 curriculum.
The goal is to solve the classic *Dining Philosophers Problem* using **threads** and **mutexes**, ensuring proper synchronization without data races or deadlocks.

Philosophers sit around a table, alternating between eating, sleeping, and thinking. Each philosopher must take two forks (mutexes) to eat, and the simulation ends when a philosopher dies or when all have eaten a required number of times (if specified).

## 🚀 Features

* Each philosopher is represented by a **thread**.
* Forks are protected with **mutexes**.
* Philosophers alternate between **eating**, **sleeping**, and **thinking**.
* Simulation stops when a philosopher dies or when all philosophers have eaten the required number of times (optional).
* Logs are synchronized to prevent overlapping messages.

## 🛠️ Usage

### Compilation

```bash
make
```

### Execution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

* `number_of_philosophers` → number of philosophers and forks
* `time_to_die` (ms) → max time a philosopher can live without eating
* `time_to_eat` (ms) → time spent eating
* `time_to_sleep` (ms) → time spent sleeping
* `[number_of_times_each_philosopher_must_eat]` (optional) → if set, simulation stops once all philosophers have eaten at least this many times

### Example

```bash
./philo 5 800 200 200
```

➡️ Runs a simulation with 5 philosophers, each dying if they don’t eat within 800 ms, eating for 200 ms, then sleeping for 200 ms.

## 📖 Logs format

* `timestamp_in_ms X has taken a fork`
* `timestamp_in_ms X is eating`
* `timestamp_in_ms X is sleeping`
* `timestamp_in_ms X is thinking`
* `timestamp_in_ms X died`

> `timestamp_in_ms` = elapsed time since simulation start
> `X` = philosopher ID

## ✅ Requirements

* Written in **C** according to \[42 Norm v4]
* No **global variables**
* No **data races**
* Proper memory management (no leaks)

## 📂 Project structure

```
philo/
│── includes/
│   └── philosopher.h
│── src/
│   ├── code.c
│   ├── ...
│── Makefile
```
