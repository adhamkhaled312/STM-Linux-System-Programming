#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>

// Define a structure to represent a partition entry
typedef struct {
    uint8_t status;		// Status of the partition
    uint8_t first_chs[3];	// First cylinder/head/sector address
    uint8_t partition_type;	// Type of the partition
    uint8_t last_chs[3];	// Last cylinder/head/sector address
    uint32_t lba;		// Logical block address of the partition's first sector
    uint32_t sector_count;	// Number of sectors in the partition
} PartitionEntry;

int main(int argc, char **argv)
{
    // Buffer to store data read from the disk
    char buf[512];

    // Open the disk device file for reading
    int fd = open(argv[1], O_RDONLY);

    // Flag to track extended partition entries
    uint8_t extended_flag = 5;

    // Read the first 512 bytes (the MBR) from the disk
    read(fd, buf, 512);

    // Pointer to the partition entry array in the buffer
    PartitionEntry *table_entry_ptr = (PartitionEntry *) & buf[446];

    // Print header for partition table output
    printf("%-5s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Device",
	   "Boot", "Start", "End", "Sectors", "Size", "Id", "Type");

    // Iterate over the primary partition entries in the MBR
    for (int i = 0; i < 4; i++) {
	// Skip empty partition entries
	if (table_entry_ptr[i].sector_count == 0) {
	    continue;
	}
	// Print information about the partition
	printf("%s%-5d %-10c %-10u %-10u %-10u %0.1fG      %-10X\n",
	       argv[1],
	       i + 1,
	       table_entry_ptr[i].status == 0x80 ? '*' : ' ',
	       table_entry_ptr[i].lba,
	       table_entry_ptr[i].lba + table_entry_ptr[i].sector_count -
	       1, table_entry_ptr[i].sector_count,
	       (double) ((uint64_t) table_entry_ptr[i].sector_count *
			 512) / (1024 * 1024 * 1024),
	       table_entry_ptr[i].partition_type);

	// Check if the partition is an extended partition
	if (table_entry_ptr[i].partition_type == 5) {
	    extended_flag = i;
	}
    }

    // If there is an extended partition
    if (extended_flag <= 4) {
	// Calculate the logical block address of the extended partition
	uint32_t extended_lba = table_entry_ptr[extended_flag].lba;

	// Seek to the beginning of the extended partition
	lseek64(fd, (off64_t) extended_lba * 512, SEEK_SET);

	// Read the first 512 bytes of the extended partition
	read(fd, buf, 512);

	// Update the partition entry pointer to the entries in the extended partition
	table_entry_ptr = (PartitionEntry *) & buf[446];

	// Index for extended partition entries
	int i = 5;

	// Print information about the extended partition
	printf("%s%-5d %-10c %-10u %-10u %-10u %0.1fG      %-10X\n",
	       argv[1],
	       i,
	       table_entry_ptr[0].status == 0x80 ? '*' : ' ',
	       table_entry_ptr[0].lba + extended_lba,
	       table_entry_ptr[0].lba + table_entry_ptr[0].sector_count -
	       1 + extended_lba, table_entry_ptr[0].sector_count,
	       (double) ((uint64_t) table_entry_ptr[0].sector_count *
			 512) / (1024 * 1024 * 1024),
	       table_entry_ptr[0].partition_type);

	// Increment index for further extended partition entries
	i++;

	// Iterate over additional extended partition entries
	while (1) {
	    // Exit loop if no more extended partition entries
	    if (table_entry_ptr[1].lba == 0) {
		break;
	    }
	    // Calculate the offset of the partition entry in the extended partition
	    off64_t offset = extended_lba + table_entry_ptr[1].lba;

	    // Seek to the beginning of the partition entry
	    lseek64(fd, (off64_t) offset * 512, SEEK_SET);

	    // Read the partition entry
	    read(fd, buf, 512);

	    // Update the partition entry pointer
	    table_entry_ptr = (PartitionEntry *) & buf[446];

	    // Print information about the extended partition entry
	    printf("%s%-5d %-10c %-10lu %-10lu %-10u %0.1fG      %-10X\n",
		   argv[1],
		   i,
		   table_entry_ptr[0].status == 0x80 ? '*' : ' ',
		   table_entry_ptr[0].lba + offset,
		   table_entry_ptr[0].lba +
		   table_entry_ptr[0].sector_count - 1 + offset,
		   table_entry_ptr[0].sector_count,
		   (double) ((uint64_t) table_entry_ptr[0].sector_count *
			     512) / (1024 * 1024 * 1024),
		   table_entry_ptr[0].partition_type);

	    // Increment index for further extended partition entries
	    i++;
	}
    }
    // Close the disk device file
    close(fd);

    return 0;
}
