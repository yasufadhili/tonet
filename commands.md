
# Tonet Commands

| Command | Description | Usage |
| --- | --- | --- |
| `tonet start` | Starts the Tonet service and shares the current user's file system. | `tonet start` |
| `tonet connect` | Connects to a remote device's file system. | `tonet connect <device-name-or-ip>` |
| `tonet copy` | Copies a file from the local device to a remote device. | `tonet copy <source-file-path> <target-device-name-or-ip>` |
| `tonet share` | Shares a specific directory with a remote device. | `tonet share <directory-path> <target-device-name-or-ip>` |
| `tonet list` | Lists all devices currently connected to the local device's file system. | `tonet list` |
| `tonet disconnect` | Disconnects from a remote device's file system. | `tonet disconnect <device-name-or-ip>` |
| `tonet help` | Displays the Tonet command reference. | `tonet help` |

Here's a more detailed breakdown of each command:

**`tonet start`**
- Description: Starts the Tonet service and shares the current user's file system.
- Usage: `tonet start`
- This command initialises the Tonet service on the local device, making its file system accessible to other devices on the same network.

**`tonet connect`**
- Description: Connects to a remote device's file system.
- Usage: `tonet connect <device-name-or-ip>`
- This command allows the user to access the file system of a remote device by specifying its name or IP address.

**`tonet copy`**
- Description: Copies a file from the local device to a remote device.
- Usage: `tonet copy <source-file-path> <target-device-name-or-ip>`
- This command initiates a secure file transfer from the local device to the specified remote device.

**`tonet share`**
- Description: Shares a specific directory with a remote device.
- Usage: `tonet share <directory-path> <target-device-name-or-ip>`
- This command allows the user to share a particular directory on the local device with a remote device.

**`tonet list`**
- Description: Lists all devices currently connected to the local device's file system.
- Usage: `tonet list`
- This command displays the names or IP addresses of all remote devices that are currently connected to the local device's file system.

**`tonet disconnect`**
- Description: Disconnects from a remote device's file system.
- Usage: `tonet disconnect <device-name-or-ip>`
- This command severs the connection between the local device and the specified remote device's file system.

**`tonet help`**
- Description: Displays the Tonet command reference.
- Usage: `tonet help`
- This command provides a comprehensive list of all available Tonet commands and their usage.
