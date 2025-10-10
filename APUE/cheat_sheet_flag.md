File descriptor flags are stored as bits in an integer:

Bit positions (example, simplified):
-------------------------------------
Bit 0: O_RDONLY       -> 00000001
Bit 1: O_WRONLY       -> 00000010
Bit 2: O_NONBLOCK     -> 00000100
Bit 3: O_APPEND       -> 00001000
...

Current flags for fd (oldf):
-----------------------------
oldf = O_RDONLY | O_APPEND
oldf = 00001001

-----------------------------
Add a flag using OR (|):
-----------------------------
Want to add O_NONBLOCK:
oldf | O_NONBLOCK
00001001 | 00000100 = 00001101

✅ Result: O_RDONLY + O_APPEND + O_NONBLOCK

-----------------------------
Remove a flag using AND + NOT (& ~):
-----------------------------
Want to remove O_APPEND:
oldf & ~O_APPEND
00001001 & 11110111 = 00000001

✅ Result: O_RDONLY only

---------------------------------------------
Rule of Thumb:
- Use OR (|) to **add a flag** while keeping all others.
- Use AND + NOT (& ~) to **remove a flag** while keeping all others.
- Always get old flags first: oldf = fcntl(fd, F_GETFL, 0)
- Then set new flags: fcntl(fd, F_SETFL, modified_flags)

