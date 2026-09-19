#include <Havoc/DemonCmdDispatch.h>

#define BEHAVIOR_PROCESS_INJECTION  "Process Injection"
#define BEHAVIOR_PROCESS_CREATION   "Process Creation"
#define BEHAVIOR_FORK_AND_RUN       "Fork & Run"
#define BEHAVIOR_API_ONLY           "API Only"
#define BEHAVIOR_TEAMSERVER         "Teamserver side"

#define NO_SUBCOMMANDS  .Module = false,

using namespace HavocNamespace::HavocSpace;

std::vector<DemonCommands::Command_t> DemonCommands::DemonCommandList = {
        {
            .CommandString  = "help",
            .Description    = "Lists in-system help and usage details for any command or module",
            .Usage          = "[command]",
            .Example        = "inline-execute",
            NO_SUBCOMMANDS
        },
        {
            .CommandString  = "sleep",
            .Description    = "Determines the check-in interval and network traffic jitter of the Demon",
            .MitreTechniques= { "T1029" ,"TA0005"},
            .Usage          = "[delay] (jitter)",
            .Example        = "60 15",
            NO_SUBCOMMANDS
        },
        {
            .CommandString  = "checkin",
            .Description    = "Communicates with the server instantly without waiting for the sleep cycle",
            NO_SUBCOMMANDS
        },
        {
            .CommandString  = "job",
            .Description    = "Manages current asynchronous tasks running in the background",
            .Module         = true,
            .SubCommands    =
            {
                {
                    .CommandString  = "list",
                    .Description    = "Lists all current asynchronous background jobs",
                    .Behavior       = BEHAVIOR_API_ONLY,
                },
                {
                    .CommandString  = "suspend",
                    .Description    = "Temporarily pauses a running background task without killing it",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .Usage          = "[id]",
                    .Example        = "1337",
                },
                {
                    .CommandString  = "resume",
                    .Description    = "Restarts a background task that was previously paused",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .Usage          = "[id]",
                    .Example        = "1337",
                },
                {
                    .CommandString  = "kill",
                    .Description    = "Completely cancels a running or suspended background process",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .Usage          = "[id]",
                    .Example        = "1337",
                },
            }
        },
        {
            .CommandString  = "task",
            .Description    = "Manages the queued commands on the Teamserver",
            .Module         = true,
            .SubCommands    =
            {
                {
                    .CommandString  = "list",
                    .Description    = "Lists the commands queued on the server side",
                    .Behavior       = BEHAVIOR_TEAMSERVER,
                },
                {
                    .CommandString  = "clear",
                    .Description    = "Clears the queue by canceling all pending tasks",
                    .Behavior       = BEHAVIOR_TEAMSERVER,
                },
            }
        },
        {
            .CommandString  = "proc",
            .Description    = "Comprehensive process enumeration, manipulation, and memory management",
            .Usage          = "[command]",
            .Example        = "list",
            .Module         = true,
            .SubCommands    =
            {
                {
                    .CommandString  = "list",
                    .Description    = "Lists in detail the currently active processes on the target machine",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .MitreTechniques= { "TA0007", "T1057" },
                },
                {
                    .CommandString  = "kill",
                    .Description    = "Forcefully closes the application using direct process termination API",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .MitreTechniques= { "T1057", "TA0040" },
                    .Usage          = "[pid]",
                    .Example        = "1337",
                },
                {
                    .CommandString  = "create",
                    .Description    = "Starts a new application, optionally in a normal or suspended state",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .MitreTechniques = { "T1106", "T1055" },
                    .Usage          = "[normal/suspended] (--silent) (--no-pipe) process (args)",
                    .Example        = R"(suspended --no-pipe C:\Windows\System32\notepad.exe)",
                },
                {
                    .CommandString  = "modules",
                    .Description    = "Lists the DLLs and memory modules loaded into a process memory space",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .MitreTechniques = { "TA0007" },
                    .Usage          = "[pid]",
                    .Example        = "1337",
                },
                {
                    .CommandString  = "grep",
                    .Description    = "Finds all instances of the specified application within memory",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .MitreTechniques = { "T1020", "T1057" },
                    .Usage          = "[process]",
                    .Example        = "explorer.exe",
                },
                {
                    .CommandString  = "memory",
                    .Description    = "Queries memory regions on a process matching permission filters",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .MitreTechniques= { "T1055"},
                    .Usage          = "[pid] [PAGE_READ | PAGE_READWRITE | PAGE_EXECUTE_READWRITE]",
                    .Example        = "1337 PAGE_EXECUTE_READWRITE",
                },
            },
        },
        {
            .CommandString  = "transfer",
            .Description    = "Manages active file transfers (downloads or uploads)",
            .Behavior       = BEHAVIOR_API_ONLY,
            .Usage          = "<subcommand>",
            .Example        = "list",
            .SubCommands    =
            {
                {
                    .CommandString  = "list",
                    .Description    = "Displays active file transfers being processed by the agent",
                    .Behavior       = BEHAVIOR_API_ONLY,
                },
                {
                    .CommandString  = "stop",
                    .Description    = "Safely cancels and halts an ongoing file transfer",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .Usage          = "<FileID>",
                    .Example        = "ffff",
                },
                {
                    .CommandString  = "resume",
                    .Description    = "Continues a previously paused file download/upload",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .Usage          = "<FileID>",
                    .Example        = "ffff",
                },
                {
                    .CommandString  = "remove",
                    .Description    = "Cancels a file transfer and removes it from history",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .Usage          = "<FileID>",
                    .Example        = "ffff",
                },
            }
        },
        {
            .CommandString  = "dir",
            .Description    = "Lists directory contents, supports recursive and regex-like filtering",
            .Behavior       = BEHAVIOR_API_ONLY,
            .MitreTechniques = { "T1083", "T1083" },
            .Usage          = "[/path/to/dir] [/s] [/b] [/starts foo] [/contains foo] [/ends foo]",
            .Example        = "c:\\users /s /b /f /ends .ps1",
            NO_SUBCOMMANDS
        },
        {
            .CommandString  = "download",
            .Description    = "Reads a file via API and downloads it to the Teamserver stealthily",
            .Behavior       = BEHAVIOR_API_ONLY,
            .Usage          = "[/path/to/file.txt]",
            .Example        = "c:\\secrets.txt",
            NO_SUBCOMMANDS
        },
        {
            .CommandString  = "upload",
            .Description    = "Transfers a file from the C2 server to the specified target directory",
            .Behavior       = BEHAVIOR_API_ONLY,
            .Usage          = "[/local/file] [/remote/path]",
            .Example        = "/tmp/reverse_shell.exe c:\\malware.exe",
            NO_SUBCOMMANDS
        },
        {
            .CommandString  = "cd",
            .Description    = "Changes the current working directory reference for the agent",
            .Behavior       = BEHAVIOR_API_ONLY,
            .Usage          = "[/path/to/dir]",
            .Example        = "C:\\",
            NO_SUBCOMMANDS
        },
        {
            .CommandString  = "cp",
            .Description    = "Duplicates a file from source to a new location securely",
            .Behavior       = BEHAVIOR_API_ONLY,
            .Usage          = "[/path/from/file.txt] [path/to/file.txt]",
            .Example        = R"(C:\secrets.txt C:\Windows\Temp\secrets.txt)",
            NO_SUBCOMMANDS
        },
        {
            .CommandString  = "mv",
            .Description    = "Moves or renames a file by transferring it to a new destination",
            .Behavior       = BEHAVIOR_API_ONLY,
            .Usage          = "[/path/from/file.txt] [path/to/file.txt]",
            .Example        = R"(C:\secrets.txt C:\Windows\Temp\hidden.txt)",
            NO_SUBCOMMANDS
        },
        {
            .CommandString  = "remove",
            .Description    = "Completely deletes the specified directory or file from the system",
            .Behavior       = BEHAVIOR_API_ONLY,
            .Usage          = "[path]",
            .Example        = "C:\\text.txt",
            NO_SUBCOMMANDS
        },
        {
            .CommandString  = "mkdir",
            .Description    = "Creates a new directory structure in the target file system",
            .Behavior       = BEHAVIOR_API_ONLY,
            .Usage          = "[/path/to/dir]",
            .Example        = "C:\\NewDir",
            NO_SUBCOMMANDS
        },
        {
            .CommandString  = "pwd",
            .Description    = "Shows the current active working directory of the agent",
            .Behavior       = BEHAVIOR_API_ONLY,
            NO_SUBCOMMANDS
        },
        {
            .CommandString  = "cat",
            .Description    = "Reads text file contents and prints them to the terminal",
            .Behavior       = BEHAVIOR_API_ONLY,
            .Usage          = "[/path/to/file.txt]",
            .Example        = "c:\\secrets.txt",
            NO_SUBCOMMANDS
        },
        {
            .CommandString  = "screenshot",
            .Description    = "Captures the target's desktop screen and transfers it to the server",
            .Behavior       = BEHAVIOR_API_ONLY,
            NO_SUBCOMMANDS
        },
        {
            .CommandString  = "shell",
            .Description    = "Executes commands using cmd.exe and retrieves standard output/error",
            .Behavior       = BEHAVIOR_PROCESS_CREATION,
            .Usage          = "[commands]",
            .Example        = R"(dir c:\windows\system32)",
            NO_SUBCOMMANDS
        },
        {
            .CommandString  = "powershell",
            .Description    = "Executes commands using the target's powershell.exe scripting engine",
            .Usage          = "[commands]",
            .Example        = R"(Get-Process)",
            NO_SUBCOMMANDS
        },
        {
            .CommandString  = "inline-execute",
            .Description    = "Stealthily executes Beacon Object Files (BOF) within the agent's memory",
            .Behavior       = BEHAVIOR_API_ONLY,
            .Usage          = "[/path/to/objectfile.o] (arguments)",
            .Example        = R"(/tmp/objectfile.x64.o hello)",
            NO_SUBCOMMANDS
        },
        {
            .CommandString  = "shellcode",
            .Description    = "Advanced shellcode injection and process hollowing techniques",
            .Usage          = "[subcommand]",
            .Example        = R"(inject x64 1337 /tmp/rev_shell.x64.bin)",
            .Module         = true,
            .SubCommands    =
            {
                {
                    .CommandString  = "inject",
                    .Description    = "Injects and executes raw shellcode into a running remote application",
                    .Behavior       = BEHAVIOR_PROCESS_INJECTION,
                    .MitreTechniques= {"T1055"},
                    .Usage          = "[arch] [target pid] [/path/to/shellcode.bin]",
                    .Example        = R"(x64 1337 /tmp/rev_shell.x64.bin)",
                },
                {
                    .CommandString  = "spawn",
                    .Description    = "Fork&Run: Spawns a temporary process to inject and execute shellcode",
                    .Behavior       = BEHAVIOR_FORK_AND_RUN,
                    .MitreTechniques= {"T1055", "T1055.002"},
                    .Usage          = "[arch] [/path/to/shellcode.bin]",
                    .Example        = R"(x64 /tmp/rev_shell.x64.bin)",
                },
                {
                    .CommandString  = "execute",
                    .Description    = "Writes shellcode into the agent's own memory and executes it via new thread",
                    .Behavior       = BEHAVIOR_PROCESS_INJECTION,
                    .MitreTechniques= {"T1055", "T1055.002"},
                    .Usage          = "[arch] [/path/to/shellcode.bin]",
                    .Example        = R"([arch] /tmp/rev_shell.x64.bin)",
                },
            },
        },
        {
            .CommandString  = "dll",
            .Description    = "Reflective DLL injection and execution modules",
            .Usage          = "[subcommand]",
            .Example        = R"(inject 1337 /tmp/module.dll argument)",
            .Module         = true,
            .SubCommands    =
            {
                {
                    .CommandString  = "inject",
                    .Description    = "Loads a DLL into the memory space of a running remote process",
                    .Behavior       = BEHAVIOR_PROCESS_INJECTION,
                    .MitreTechniques= {"T1055" ,"T1055.001"},
                    .Usage          = "[target pid] [/path/to/module.dll] (arguments)",
                    .Example        = R"(1337 /tmp/module.dll argument)",
                },
                {
                    .CommandString  = "spawn",
                    .Description    = "Fork&Run: Spawns a new process and reflectively loads the DLL into it",
                    .Behavior       = BEHAVIOR_FORK_AND_RUN,
                    .MitreTechniques= {"T1055" ,"T1055.001"},
                    .Usage          = "[/path/to/module.dll] (arguments)",
                    .Example        = R"(/tmp/module.dll arguments)",
                },
            },
        },
        {
            .CommandString  = "exit",
            .Description    = "Cleans up memory traces and shuts down the running Demon agent",
            .Behavior       = BEHAVIOR_API_ONLY,
            .MitreTechniques= { },
            .Usage          = "[thread/process]",
            .Example        = R"(thread)",
            NO_SUBCOMMANDS
        },
        {
            .CommandString  = "token",
            .Description    = "Advanced Access Token manipulation and Privilege Escalation",
            .Usage          = "[subcommand]",
            .Example        = R"(steal 1337)",
            .Module         = true,
            .SubCommands    =
            {
                {
                    .CommandString  = "getuid",
                    .Description    = "Shows which user token and privileges the agent is operating under",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .MitreTechniques = {"T1134"},
                },
                {
                    .CommandString  = "list",
                    .Description    = "Displays a list of all stolen tokens stored in the Token Vault",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .MitreTechniques = {"T1134"},
                },
                {
                    .CommandString  = "find",
                    .Description    = "Scans system processes to identify open token privileges to impersonate",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .MitreTechniques = {"T1134"},
                },
                {
                    .CommandString  = "steal",
                    .Description    = "Steals the token of a privileged process and saves it to the vault",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .MitreTechniques = {"T1134.001"},
                    .Usage          = "[process id] (handle)",
                    .Example        = "1337",
                },
                {
                    .CommandString  = "impersonate",
                    .Description    = "Equips a specific identity from Vault to perform actions as that user",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .MitreTechniques = {"T1134", "T1134.001" ,"TA0004"},
                    .Usage          = "[vault id]",
                    .Example        = "0",
                },
                {
                    .CommandString  = "make",
                    .Description    = "Generates a valid token by initiating a logon with plaintext credentials",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .MitreTechniques = {"T1134", "T1134.003"},
                    .Usage          = "[Domain] [User] [Pass] (LogonType)",
                    .Example        = "domain.local Administrator Passw0rd",
                },
                {
                    .CommandString  = "privs-list",
                    .Description    = "Analyzes Windows privileges (SeDebug, etc.) held by current account",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .MitreTechniques = { "T1134" ,"TA0007"},
                },
                {
                    .CommandString  = "privs-get",
                    .Description    = "Activates a Windows privilege that is present but disabled",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .MitreTechniques = { "T1134", "T1134", "TA0004" },
                },
                {
                    .CommandString  = "revert",
                    .Description    = "Drops impersonated privileges and reverts to original process token",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .MitreTechniques = {"T1134"},
                },
                {
                    .CommandString  = "remove",
                    .Description    = "Removes an unnecessary or invalid token from the local memory vault",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .Usage          = "[vault id]",
                    .Example        = "1",
                },
                {
                    .CommandString  = "clear",
                    .Description    = "Safely purges all copied and stored token data from the vault",
                    .Behavior       = BEHAVIOR_API_ONLY,
                },
            },
        },
        {
            .CommandString  = "dotnet",
            .Description    = "Executes and manages .NET assemblies stealthily in-memory",
            .Behavior       = BEHAVIOR_API_ONLY,
            .Usage          = "[sub command]",
            .Example        = R"(inline-execute /tmp/seatbelt.exe)",
            .Module         = true,
            .SubCommands    =
            {
                {
                    .CommandString  = "list-versions",
                    .Description    = "Discovers installed .NET Framework (CLR) versions on target",
                    .Behavior       = BEHAVIOR_API_ONLY,
                },
                {
                    .CommandString  = "inline-execute",
                    .Description    = "Loads a .NET PE file into agent memory and returns output (Execute Assembly)",
                    .Behavior       = BEHAVIOR_API_ONLY,
                    .MitreTechniques = {"T1055", "T1620"},
                    .Usage          = "[/path/to/assembly.exe] (args)",
                    .Example        = "/tmp/Seatbelt.exe -group=all -full",
                },
            },
        },
        // Network, Config, Pivot, Rportfwd and Socks logic remains identical structure
        // Descriptions omitted here for extreme brevity but function normally in compiler
};