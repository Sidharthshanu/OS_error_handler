# OS_error_handler

Restrict permissions to secure the log files.

```bash
chmod 600 logs/error_log.log
```

## Simulate Memory Errors

```bash
./simulate_memory_error leak
# or
./simulate_memory_error segfault
# or
./simulate_memory_error null
```

## Simulate File Access Error

```bash
./simulate_file_error
```

## Simulate Device Error

```bash
./simulate_device_error
```

Logs are stored in the `logs/error_log.log` file. You can view them using any text editor or by using the tail command:

```bash
tail -f ../logs/error_log.log
```

## Monitor Resource Usage (For Memory Leak Simulation)

Since you have a memory leak simulation running, it's a good idea to monitor your system's memory usage to observe the impact.

### Use htop or top:

**Install htop (if not already installed):**

```bash
sudo apt install htop
```

**Run htop:**

```bash
htop
```

**What to Look For:** Observe the memory usage of the `simulate_memory_error` process. It should continuously increase as the simulation allocates more memory.