#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	if(argc<2)
	{
		printf("some argument missing\n");
		return -1;
	}

	char* file = argv[1];
	int fd;
	int ch;
	struct flock lock;

	printf("1. Set a read lock\n");
	printf("2. Set a write lock\n");
	printf("Enter your choice\n");
	scanf("%d", &ch);
	
	if(ch==1)
	{
		char c;
		printf ("opening %s\n", file);      /* Open a file descriptor to the file. */
		fd = open (file, O_RDONLY);
		printf ("locking the file...\n");
		memset (&lock, 0, sizeof(lock));    /* Initialize the flock structure. */
		lock.l_type = F_RDLCK;
		fcntl (fd, F_SETLKW, &lock);      /* Place a read lock on the file. */
		printf ("locked\n");

		printf ("Enter u to unlock \n");			/* Wait for the user to hit Enter. */
		c=getchar();
		c=getchar(); 
		if(c=='u')
		{
			printf ("unlocking...\n");				/* Release the lock. */
			lock.l_type = F_UNLCK;
			fcntl (fd, F_SETLKW, &lock);
			printf ("unlocked\n");
		}
		close (fd);
	}

	else if(ch==2)
	{
		char c;
		printf ("opening %s\n", file);      /* Open a file descriptor to the file. */
		fd = open (file, O_WRONLY);
		printf ("locking the file...\n");
		memset (&lock, 0, sizeof(lock));    /* Initialize the flock structure. */
		lock.l_type = F_WRLCK;
		fcntl (fd, F_SETLKW, &lock);      /* Place a write lock on the file. */
		printf ("locked\n");

		printf ("Enter u to unlock \n");			/* Wait for the user to hit Enter. */
		c=getchar();
		c=getchar(); 
		if(c=='u')
		{
			printf ("unlocking...\n");				/* Release the lock. */
			lock.l_type = F_UNLCK;
			fcntl (fd, F_SETLKW, &lock);
			printf ("unlocked\n");
		}
		close (fd);
	}

	return 0;
}