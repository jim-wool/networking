dickinbaus 
- cd:
	.: dir im at
	..: dir one level up
	~: home dir
	-: last dir

- ls:
	-i: shows the index node
	-a: shows hidden files too (*)
	-l: long format (*)
	-h human readable
	-r: reversed
	-t: sort by modification time
	-d: list the dir itself instead of its contents (*)
	-S: sort by file size
you can combine these

- touch:
	- creates a new file
	- updates an existing file's timestamp
	(ls -l filename to see that shit)
	-c: do not create the file if it doesn't exist
	-a: change only the access time
	-m: change only the mod time
	-d "DATE": use a specific date string
	-r FILE: use another file's timestamp as a ref
	-t STAMP: use a timestamp in a compact numeric form
	
- file:
	shows description of the file's contents
	-i: prints MIME type info
	-b: brief mode

- cat:
	shows the file's contents
	- with multiple files: prints combined output
exmple: cat > file: start writing in "file", ctrl + d on a new line to save and exit. (>: write)
(>>: append)

- less: cat but cooler

- history:
	- shows recently executed commands
	- !! + enter: execute the latest command
	- !NUMBER: execute command
	- !NAME: execute the most recent command that starts with NAME
	-c: clears history
	-w: saves history
	-d <offset>: delete a specific entry

- cp multiple files /path/to/dest
	-r: recursively, to copy a directory (cp -r stuff stuffdest)
	-i: interactive flag
	-f: force, no prompts
	-n: prevents overwriting
	-p: preserve file attributes
	-a: archive mode
	-u: copy only when the source is newer than the dest
	-v: show each file as it is copied

- mv: used for renaming and moving
(mv oldname newname)
(mv my files /path/to/dest)
(mv -t /path/to/dest my files lmao)

- mkdir: (mkdir dir1 dir2 dir3)
	-p: for nested directories
	-m <permission mode>
	-v: verbose

- rm:
	-i: interactive
	-f: force (the famous rm -rf incidents)

- find: (find PATH expression)
	-name: actual name, or "*.ext" for certain extensions
	-type: d for dirs, f for files
	-size
	-mtime: modification time (-mtime -7: within the last 7 days, +30: more than 30 days ago	
)

- help: help + bash built-in commands, not external ones

- type: tells you whether a command is a bash built-in or an external one

- whatis: one-line description of an external command

- man: shows manual

- alias: (ex: alias ll="ls -la")
	- these are temporary by default
	- in order to make permanent aliases, edit .bashrc

- unalias: removes an alias

- source ~/.bashrc: reloads bash config

- exit: exits shell session (<=>: Ctrl-D is an EOF signal)

- logout: terminates a login shell

___________________________________________

- >: redirection operation: it intercepts the data heading to stdout and sends it to a new location (wipes existing content)

- >>: appends the output to the end of the file

- <: redirects stdin for a command, making it read from a new location instead of the keyboard (for example: cat < file.txt > f1.txt)

- default file descriptors:
	0: stdin, 1: stdout, 2: stderr

- discarding error messages:
(ex: ls /fake/dir 2 > /dev/null)

- pipe operator: takes the standard output of the command on its left and uses it at the standard input of the command on its right

- tee command: reads from the stdin and writes to stdout and one or more files, commonly used with the pipe operator

___________________________________________

- accessing variables: prefix them with $
	-$HOME: basically ~
	-$USER: current username
	all of this is stored in the shell's environment

- env: displays the environment variables

- Setting an env var for the current session:
export KEY=value
	- to make persistent vars, edit the .bashrc file

- cut: extract portions of text from a file
i have no fucking clue what this will be useful for

- paste: what

- head: by default, displays the 10 first lines of any file
	-n: specify the number of lines

- tail: same stuff as head
	-f: real time monitoring

- expand: converts tabs into spaces, and prints the converted content, by default 1 tab = 8 spaces, to save use the redirection operator (duh)(dont redirect to the same file tho lmao)
	the bijection is: unexpand -a (-a because by default it only converts the leading spaces)

- join: combines lines from two sorted files based on an identical first field

- split: divides a large file into smaller ones

- sort + file name:
	-r: reversed
	-n: by numerical value

- tr: translates, deletes, or squeezes characters from stdin (lotta pipping)
examples:
	echo "hi" | tr a-z A-Z (from one range to another)
	echo "hi/hello" | tr '/' '-' (replace)
	echo "abc123" | tr "abc" "ABC"
	-d: deletes characters
	echo "hi123" | tr -d '0-9'
	echo "hi, world!" | tr -d '[:punt:]' (removes punctuation)
	printf "1\n2" | tr -d '\n'
	-s: squeezing repeated characters: replace each run of a listen character with one instance of that character
	echo "hi   yo   lol" | tr -s ' '
characters classes:
[:lower:], [:upper:], [:digit:], [:alpha:], [:alnum:], [:space:], [:punct:]
	-c: complements

transformation streams: just combine tr commands with the | operator
(in a nutshell, tr x y is like String.replace(x, y))

to read from a file, use the < operator

- uniq:
	* for collapsing adjacent duplicate lines
	-c: for counting adjacent groups
	-u: for printing unique groups (containing exactly one line)
	-d: the opposite of -u (-d prints once, -D every line)
	if the duplicates aren't ajacent, sort first

- wc: counts properties of text streams
ex: printf "red blue\ngreen\n" | wc -> 2 3 15
2: new lines, 3: whitespaces and 15 bytes of ascii
	-l: \n characters only
	-w: word count
	-c : byte count
	-m: character count

- nl: just adds numbers to lines bro, by default skips blank ones
	-ba: numbers all lines
	-w {number}: sets the number field's width
	-s: changes the separator after the number

- grep: selects input lines that match a pattern (takes one or more input files)
	-F: to treat the pattern as a fixed string rather than a regexp
	-E: extended regexps, including operators such as |, +, and ? without backslashes (\ makes an operator a literal)
	^ and $ match the beginning and end of a line
	-e PATTERN: to supply a pattern explicitly, especially when a patter begins with a - (-e can be repeated)
	-f patterns.txt to read one pattern per line from a file
	-i: case insensitive
	-n: prefix selected lines with line numbers
	-v: select lines that DO NOT match
	-c: print the count of selected lines
	-o: print only the matching part
(you can combine them obviously)
	-r: research readable files recursively below a directory (grep -r pattern dir)

___________________________________________
Regex bullshit:

*: repeats the preceeding character 0 or more times
^ and $: already known
.: matches one character (\. for a literal period)

a bracket expression matches one character from a specific SET!!!! (this shit [])
when ^ is the first character after [, it negates the set

ranges can describe characters between endpoints (a-z for example, $1-$2 is a range) ( d[a-c]g matches dag or dbg or dcg)

in ERE mode:
+: 1 or more repetitions
?: 0 or 1 repetition
|: either the expression on the left or on the right
(...): group expressions

___________________________________________

- command: displays information about a command
(use with -v)

- vimtutor

- vim search patters:
	/pattern: after cursor
	?pattern: before cursor
n or N to switch between results

searching for the word under the cursor: in normal mode, place the cursor under the word, and use * or #
\c inside a pattern to ignore case

h: left, j: down, k: up, l: right
w: move to the beginning of the next word
b: move to the beginning of the current or previous word
e: move to the end of the current or next word
^: move to the first nonblank character
$: move to the end of the line
d: delete text and dd: deletes the whole line
y: copy text (yank)
x: delete the character under the cursor
ndd: delete n lines starting with the current line
u: undo

___________________________________________

- id: displays the current process identity information

- sudo -l: shows the commands the current account is allowed to run

- su: substitute user, starts a shell or a command with another user's identity, with no username, the target defaults to root

- sudo COMMAND: requests authorization to run one command as a target user, usually root by default
(use sudo -u USER to specify which user)

- /etc/passwd: stores local account records in a colon-separated text format.

- getent: queries the resolved passwd db
	getent passwd
	getent passwd root returns:
login name:password (usually an x):UID:GID:comment:home dir:login shell

passwords live in /etc/shadow and are hashed

login name:password hash:last password change: minimum password age:maximum password age:warning period: inactivity period:acount expiration date: reservation field

/etc/group: stores local group records. It maps group names to numeric GIDs and lists explicit members, supporting access control shared by several accounts

cat /etc/group
getent queries the resolved group db
group name:password field:GID:memberlist(comma separated)

________________________________________________

User management

useradd -D: shows the default options for creating local users
useradd -m -s /bin/bash -c "comment" username (-m: explicitely creates home dir)

to change a local user's password interactively: use passwd
an authorized admin can set another local account's password with sudo password <user>
admins can lock/unlock the password with passwd -l/-u USER

userdel USER removes the local account records but normally leaves the home dir
userdel -r USER attempts to remove the home dir

__________________________________________________________________
Permissions:

ls -l: displays a long listing

example: drwxr-xr-x 2 pete penguins 4096 Dec 1 11:45 Desktop/
	 ^ ^  ^  ^      ^     ^
let examine every character:
1st character: -: regular file, d: directory, l: symbolic link

Modifying permissions (chmod nigga)
chmod changes the mode bits of files and directories (normally only the file owner or a privileged process can make this change)

A symbolic mode states which permission class to change, how to change it and which permissions are involved
. u: owner, g: group, o:other, a:all, +: adds, -: removes, =: sets
(ex: chmod u+x file, chmod ug+w file, chmod g-x file, chmod g=r, o= file)

The octal mode was discussed in class lowkey...

Ownership permissions

chown: assign a different user owner (ex: sudo chown new_user myfile)

chgrp: changes the group owner

changing the user and group together: chown new_user:new_owner file

umask: prevents selected permission bits from being set when that process creates a filesystem object.
resulting mode = requested mode AND NOT umask

many ordinary programs request 0666 for new regular files, because creating executable files by default would be unsafe, they commonly request 0777 for new dirs
with umask 0022:
regular file: 0666 masked by 0022 -> 0644 (rw-r--r--)
directory: 0777 masked by 22 -> 0755 (rwxr-xr-x)
changing the umask in one shell does not alter its parent process or unrelated sessions.

Setuid: is not a general instruction to run as root, its effect depends on the executable's owner, the os, the fs and mount options, and the credentials management
-rwsr-xr-x 1 root root 68248 Jan 10 09:30 /usr/bin/passwd
the lowercase s in the owner's exec position means both setuid and owner execute are set
setuid is set symbolically with: sudo chmod u+s file (in octal: it contributes 4 in a leading special bits digit)
(example: setuid basically says to the sys wherever it is set, run the file with the permission of the owner of the file, typically, it is run against a file owned by root, like setting passwords, it is a root operation but because the s bit exists on the permission list, any user can change their own pass)
("anyone who can get to that utility will run it as root") (the octal equivalent: 4)

Setgid: allows you to run a file as a member of the file group (g+s)
(s: both setgid and execute are set. S: only setgid is set) (the octal equivalent: 2)

Sticky bit: makes everyone read or write from or to a file without deleting anything
it does not grant write or search access: it only restrics removal and rename
(t: both sticky and others execute are set. T: only sticky is set)
it makes shared writable directories safer, ordinary read and write permissions are stil required however
(example: ls -ld /tmp: everyone can add or modify files but only root can delete files)
(sudo chmod +t ..) (the octal equivalent: 1)

The effective user id: the user credential used for many fs and privilege checks, ordinarily it matches the real UID. Executing an honored setuid program can instead initialize it from the executable's owner.
Saved set-user-id: lets a program retain an identity it may later restore, subject to the syscall rules.

__________________________________________________________________

Process: a running instance of a program. Linux identifies each live process with a PID

ps: takes a snapshot of the running processes (nothing too detailed)

ps aux: shows it like this
USER         PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root           1  0.0  0.2  23908 14552 ?        Ss   17:48   0:01 /sbin/init
root           2  0.0  0.0      0     0 ?        S    17:48   0:00 [kthreadd]

a: expands selection to processes belonging to other users that have terminals
x: includes processes without controlling terminals, broadens a
u: selects a user-oriented output (with % usage and fancy stuff)

the widely used standard style command: ps -ef
UID          PID    PPID  C STIME TTY          TIME CMD
root           1       0  0 17:48 ?        00:00:01 /sbin/init
root           2       0  0 17:48 ?        00:00:00 [kthreadd]

-e: select every process visible to the caller
-f: full-format listing

pstree: shows hierarchical processes

top: an interactive view that refreshes periodically

___________________________________________________________________________

Controlling terminal: a terminal device associated with the session and used by the kernel to terminal-generated signals and job control. The TTY field in process listings helps identify that association
The name TTY comes from historical teletypes. On modern linux, terminal interfaces are device abstractions rather than necessarily physical equipment.

a system virtual console can appear under a name such as tty1.
(pts is a pseudo terminal)
use the command tty to display the terminal connected to the current command's stdin (/dev/pts/0)

a controlling terminal belongs to a session, not merely to the command that happened to open a window.
a ? means that the process has no controlling terminal

_____________________________________________________________________________

A program is executable code and data stored in a file. A process is a live execution context. The same program can have many independent process instances.

The kernel maintains the info required to schedule and control each process: process and parent identifiers, user and group credentials, virtual mem mappings, ...
Some underlying resources can be shared. Related processes may share mapped memory, and threads in one process share an address space and many process-wide resources. A process therefore provides isolation boundaries without implying that every byte or kernel object is physically private.

Runnable threads (ways to separate chunks of code into separate blocks that can be executed by the cpu at the same time, the main diff between threads and processes is that the latter get assigned their own memory space that by default other processes can't touch. While threads do share the heap memory within a process) compute for CPU time. The kernel scheduler chooses which thread runs on which cpu according to many factors, this is not a promise that every process receives a fair share.

When a process exists, the kernel releases most of its private resources, closes remaining descriptors and records termination info for its parent

Background processes: a process that runs while you can continue using your terminal
(end the command with &)
watch: executes a command periodically, showing output fullscreen.
	-n: seconds to wait between updates

run process in foreground: watch -n time something
suspend it: ctrl-Z
move it to background and resume it: bg
bring it back to foreground: fg

renice PRIORITY_NUM -p PID: changes process priority
jobs: displays status of jobs

_________________________________________________________________

Process creation:
Linux processes form parent-child relationships. A shell commonly starts an external command by creating a child process and arranging for that child to execute the request program.

Creating a child with "fork"

The fork() syscall creates a child process based on the calling process. Parent and child continue from the return point of fork, but receive different return values and have different PIDs.

An "execve()" call loads a new program into the calling process. On success it replaces the process image and does not return to the old program. The PID remains intact (execve does not create a new process)

Many shell commands therefore follow a fork-exec pattern:
1. the shell creates a child 2. the child prepares redirections and other exec state 3. the child executes the request program 4? the shell waits or continues depending on the fg or bg exec.

PID identifies the process while PPID identifies its parent

A process can finish by returning from its main function, calling an exit interface or being terminated by a signal. The kernel releases most of its resources but parent-child accounting continues until the parent collects the termination info.

Exit status: 0 means success, and a nonzero val reports some form of failure or alternate outcome

The kernel recorsd how a child terminated and notifies its parent. The parent uses a member of the wait() syscall family to retrieve that info. Collecting the records is called reaping

After a child exists and there is no termination record reap, it appears as a zombie (starts with Z in ps). It no longer execs and retains no ordinary address space.

If a parent exits while its child remains, the kernel reparents that child to an eligible subreaper or to the init process. The child may be running, sleeping, stopped or later become a zombie. Orphan describes the loss of the original parent

lsblk: shows partitions

NAME   MAJ:MIN RM  SIZE RO TYPE MOUNTPOINTS
sda      8:0    0   20G  0 disk 
├─sda1   8:1    0 18.9G  0 part /
├─sda2   8:2    0    1K  0 part 
└─sda5   8:5    0  1.1G  0 part [SWAP]
sr0     11:0    1 50.7M  1 rom  

meddy@mediocre:~$ df -h .
Filesystem      Size  Used Avail Use% Mounted on
/dev/sda1        19G  6.4G   12G  37% /

shows which partition the current dir is in

Signals:
A signal is an async notification delivered to a process or a particular thread. Signals report events and request actions but carry only limited info compared with data-oriented interprocess comms mechanisms
They can originate in several places:
- SIGINT for Ctrl-C or SIGSTP for Ctrl-Z
- The kernel can generate a synchronous signal such as SIGSEGV when a thread makes an invalid mem ref
- A process can send an authorized signal to another process or process group

A signal can have either of these three responses:
- the predefined default action
- ignore the signal
- invoke a user-installed handler

kill -l: inspect local mapping of singals (name to number)

unlike SIGKILL, SIGTERML can be caught so a program can initiate its own shutdown logic

Threads have signal masks that can temporarily block delivery of selected signals.

SIGKILL terminates a process and SIGSTOP stops it. Neither signal can be caught, ignored, or blocked.
(SIGKILL provides no opportunity for application cleanup)

kill: sends a signal to a process or process group.
with a PID only as an arg, it sends a SIGTERM by default
kill -TERM PID
SIGTERM has a default action of termination, but a program can catch it or ignore it. (stop accepting work, save state, release resources, etc)

check if a process with a specific PID exists:
kill -0 PID


Process niceness:
A nice value is one input for ordinary time-sharing policies. Linux can execute threads simultaneously on different CPU cores and time-share a core among more runnable threads than it can run at once. The scheduler makes those choices according to scheduling policy, priority, affinity and workload.

The range of niceness is from -20 to 19
lower => greater scheduling weight, higher => less relative weight (makes it nicer)

ps -o pid,ni,prii,stat,cmd

starting a command: nice -n <val> <long_computation> (val necessitates certain privileges based on its value)

changing an existing process: renice -n <val> -p PID


States:
A linux tast moves between execution states as it runs, waits, stops, and exists. The STAT field from ps captures one moment

The first character in STAT is the primary state. Additional characters are modifiers describing properties such as session leadership or foreground process-group membership.
R -> running
S -> interruptible sleep. The task is waiting for an event and can be awakened by an appropriate one
D -> uninterruptible sleep. A brief D state can be normal, persistent or numerous D tasks can indicate slow, unavailable or faulty I/O
T -> stopped by job control, such as SIGSTP or SIGSTOP
Z -> zombie process, the process has exited but its parent has not yet collected the termination record

Resume a job-control stop with SIGCONT when appropriate. A zombie cannot be resumed or killed because it is no longer executing

Listing /proc (ls /proc)

Reading process info
less /proc/PID/status

Other useful entries: /cmdline, /maps, /environ, /cwd ...

System-wide interfaces
/proc/cpuinfo
/proc/meminfo
/proc/mounts
/proc/sys/
remember ps, free and top

Jobs
Append & to start a pipeline asynchronously
$ sleep 1000 &

the shell returns a prompt without waiting for the job to finish. Background status does not automatically redirect output, detach the controlling terminal or make the job survive logout. Redirect input and output explicitly when required, and use a service manager, scheduler, or terminal multiplexer for work that must outlive the interactive shell.w

A background job that attempts to read from the controlling terminal is normally stopped with SIGTTIN because it is not the terminal's fg process group.

$ jobs: lists the shell jobs
The bracketed number is a shell job ID not a pid
jobs are tracked by the current shell session

When a job is in the fg, pressing Ctrl-Z normally makes the terminal send a SIGSTP to its fg process group. The shell regains control after the job stops

continue the current stopped job in the background by running the bg command: it sends a continuation signal and leaves the job outside the terminal fg.

Moving a job to the fg: fg %JOB_ID (%1 for instance)

You can signal a job using the following:
$ kill -TERM %JOB_ID


____________________________________________________________________________________

Software distribution

A binary package can contain executables, libraries, documentation, default configuration, service definitions, and other resources. It also carries metadata such as:
- package name and version, target architecture, declared dependencies and conflicts, file lists, optional scripts and triggers.

Two widely used native formats are:
- .deb: used by debian and distros derived from it including ubuntu and linux mint
- .rpm: used by fedora, RHE, and many more

A package manager records installed state and coordinates changes across packages. Installing from trusted distribution repos usually provides consistent dependency resolution, sig verification, sec updates and clean removal. 

A repository is more than a dir of archives. Its metadata describes available package names, versions, architectures, checksums, dependencies and repo sections.

to refresh configured metadata: $ sudo apt update

APT reads configured sources from both: /etc/apt/sources.list and files ending in .list or .sources under /etc/apt/sources.list.d

An archive combines a directory tree and its metadata into one stream. Compression encodes a stream to reduce its size. A .tar.gz file is conventionally a tar archive whose stream has been compressed with gzip.

to compress a file with gzip: gzip <file> (it replaces the <file> with <file>.gz, use -k to keep the input file)
to decompress: gunzip <zipped>

creating an uncompressed tar archive
$ tar -cvf project.tar file1 2 3 dir1 ..
	-c: create a new archive, -v: verbosity, -f: names the archive file
	-z: compresses it
	
Listing before extracting: treat an archive from another party as untrusted input. List its member names first: tar -tzf <file>

Extract into a newly created, nonprivileged staging dir:
$ mkdir extraction-stage
$ tar -xzf <file.tar.gz> -C extraction-stage

Package dependency: it states that one package needs another package, capability or compatible version for installation or operation. Repo-aware package managers use this metadata to calculate a consistent set of changes rather than treating each archive in isolation.

Shared lib: contains compiled code that multiple programs can map at runtime. Sharing reduces duplicated implementations and lets distros update a common lib independently, but programs depend on a compatible ABI

ELF: executable and linkable format: the standard file format for executable files, object code, shared libs and core dumps on linux and other unix-like OS

dpkg is the low-level package tool on the debian family, and rpm serves a similar role. They unpack native archives, run package lifecycle actions, and update installed-package databases. Repo-aware tools such as apt build on these lower level mechanisms.

A package archive is not equivlent to one executable file. It can contain many payload files, metadata, configuration handling, and privileged lifecycle scripts. Inspect its origin, signature or authenticated download path, metadata, and contents before installation.

dpkg -i can unpack and configure the requested archiven but it doesn't fetch missing repository dependencies. A higher-level command is usually preferable for a local archive:
$ sudo apt install ./some-package.deb

Remove an installed package with apt remove

Query installed state: dpkg-query -l

Repository-aware package managers retrieve metadata, solve dependencies, verify authenticated content, and coordinate transactions. Debian-family systems commonly use APT.

Refreshing and inspecting metadata: $ sudo apt update
Search and inspect before installation:
$ apt search pkg-name
$ apt show pkg-name

Installing packages:
$ sudo apt install pakg-name

The manager proposes dependencies and any conflicts or replacements. Do not confirm automatically until you have reviewed package origin, version, architecture, download size, disk change, removals, and newly installed dependencies.

Removing packages:
$ sudo apt remove pkg-name

On an apt system, refresh metadata and then review upgrades as separate successful steps:
$ sudo apt update
$ apt list --upgradable
$ sudo apt upgrade

Build instructions are executable code. A configure script, build def, test, or compiler plugin car run arbitrary commands as your user. Do not build untrusted source, and do not run the build itself with sudo.

a common starting point is: $ sudo apt install build-essential 

_______________________________________________________________________________________
/dev directory

Linux exposes many kernel device interfaces through special FS objects called decice nodes. Opening a device node connects an application to a kernel driver rather than to bytes stored in an ordinary file.

Entries can represent physical storage, terminals, input interfaces, logical devices, or kernel-provided pseudo-devices. 

The first character of a long-listing (ls -l) identifies the FS object type. Character and block device nodes appear as 'c' and 'b'.

Pseudo-devices: Some nodes provide kernel services without corresponding to physical hardware: /dev/null accepts and discards written data (infinite well)

Other examples include /dev/zero and /dev/urandom

Device types

The first character in an ls -l mode identifies an object's filesystem type. Under /dev, character and block special files are device nodes. Pipes and Unix domain socket nodes can also appear there

Character device nodes: a c identifies a character device. It exposes a stream-oriented or device-specific interface rather than addressable fixed-size storage blocks. (/dev/null)
"Character" doesnt mean exactly one byte, applications can read or write buffers while the driver defines blocking, framing and control bhvr

Block device nodes: a b identifies a block device. Block devices support operations such as buffered I/O, partitioning, and filesystems.
A block node is not a mounted FS. It represents a storage device or logical region; a FS can be created on it and mounted separately.

FIFOs: a p identifies a FIFO, also called a named pipe. It provides a named byte stream through which processes can communicate. The data is not persistently stored in the FIFO node after being consumed.

Socket node: an s identifies Unix-domain socket node. It names a local socket endpoint an can support connection-oriented or datagram communication, descriptor passing, ... Network sockets using Internet addresses do not necessarily have FS nodes.

Device names: Linux device names reflect the kernel subsystem and driver presenting an interface, not always the physical connector printed on the hardware.

Disks presented through the SCSI disk layer commonly use sd names. This includes many SCSI, SATA, USB-storage and virtual disks:
- /dev/sda: one whole disk
- /dev/sdb: another whole disk
- /dev/sda3: partition number 3 on /dev/sda
- /dev/sdb1: partition number 1 on /dev/sdb
