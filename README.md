
# Tonet - Real-Time File Sharing Across Devices

Tonet is a command-line tool that enables seamless real-time file system sharing between different PCs on the same network. Tonet allows one to access and manage files on remote devices as if they were local, with minimal configuration required.

## Key Features

- **Cross-Device File System Access**: Start Tonet on any device, and instantly gain access to its file system from other machines on the same network.
- **Intuitive Navigation**: Use standard Linux commands like `cd`, `mkdir`, `ls` to navigate the remote file system as if it were local.
- **Real-Time Sharing**: Specify a remote device by IP address or name, and Tonet will share the contents of a selected directory in a tabular format on your local terminal.
- **Secure File Transfer**: Copy files from one device to another using the `tonet copy` command, with the contents transferred securely over the network.
- **Minimal Configuration**: Tonet requires no complex setup - just run `tonet start` to begin sharing your file system.

## Usage

### Getting Started

1. Ensure you have Tonet installed on all devices you want to share files between.
2. On each device, run `tonet start` to begin sharing its file system.
3. To access a remote device's file system, run `tonet connect <device-name-or-ip>`.
4. You can now navigate the remote file system using standard Linux commands.

### Key Commands

- `tonet start`: Starts the Tonet service and shares the current user's file system.
- `tonet connect <device-name-or-ip>`: Connects to a remote device's file system.
- `tonet copy <source-file-path> <target-device-name-or-ip>`: Copies a file from the local device to a remote device.
- `tonet share <directory-path> <target-device-name-or-ip>`: Shares a specific directory with a remote device.

See the [Tonet Command Reference](#tonet-command-reference) for a full list of available commands and options.

## Tonet Command Reference

| Command | Description |
| --- | --- |
| `tonet start` | Starts the Tonet service and shares the current user's file system. |
| `tonet connect <device-name-or-ip>` | Connects to a remote device's file system. |
| `tonet copy <source-file-path> <target-device-name-or-ip>` | Copies a file from the local device to a remote device. |
| `tonet share <directory-path> <target-device-name-or-ip>` | Shares a specific directory with a remote device. |
| `tonet list` | Lists all devices currently connected to the local device's file system. |
| `tonet disconnect <device-name-or-ip>` | Disconnects from a remote device's file system. |
| `tonet help` | Displays the Tonet command reference. |

## Technical Details

Tonet is built using C++ and relies on UDP-based communication to enable real-time file system sharing between devices. By leveraging the low-overhead and low-latency characteristics of UDP, Tonet is able to provide a seamless and responsive file management experience across the network.

## Limitations and Future Roadmap

- **Limitations**:
  - Tonet currently only supports file system sharing within the local network. Cross-internet sharing is not yet implemented.
  - The current implementation does not provide end-to-end encryption for file transfers, which may be a concern for sensitive data.
  - Tonet is limited to read-only access for remote file systems. Write access is not yet supported.

- **Future Roadmap**:
  - Implement support for cross-internet file system sharing.
  - Add end-to-end encryption for secure file transfers.
  - Add web interface for better user experience
  - Develop write access capabilities for remote file systems.
  - Explore the feasibility of integrating with cloud storage services for remote file access.
  - Expand the command-line interface with additional features and customization options.

## Getting Started

To get started with Tonet, please visit the [installation guide](https://github.com/yasufadhili/tonet/blob/main/install.md) for detailed instructions on setting up the tool on your system.

If you encounter any issues or have suggestions for improvement, feel free to [open an issue](https://github.com/yasufadhili/tonet/issues/new) on the Tonet GitHub repository.
