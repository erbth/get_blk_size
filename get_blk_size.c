#define _GNU_SOURCE

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/fs.h>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf (stderr, "Usage: %s <device>\n", argv[0]);
		return 1;
	}

	const char *dev = argv[1];

	int fd = open(dev, O_RDONLY | O_DIRECT);
	if (fd < 0)
	{
		perror("Failed to open the device");
		return 1;
	}

	size_t blk_size;

	int ret = ioctl(fd, BLKBSZGET, &blk_size);
	if (ret != 0)
	{
		perror("IOCTL failed");
		close(fd);
		return 1;
	}

	close(fd);

	printf ("%d\n", (int) blk_size);
	return 0;
}
