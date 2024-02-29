### Description
- In the session, we wrote a program that implements fdisk -l but reads only the partition table in the MBR and does not show the logical partitions.
- The task was to extended the program to show the logical partitions if they exist.

### How to Compile and Run
To compile the program, execute the following command:
```bash
gcc myfdisk.c -o myfdisk
sudo ./myfdisk /dev/device_name
```

### Sample output
This is a comparison between output of fdisk -l and myfdisk
![image](https://github.com/adhamkhaled312/STM_System_Linux_Programming/assets/105177075/e3a7ae0c-d03f-41e5-893a-6dd39525b2c9)
