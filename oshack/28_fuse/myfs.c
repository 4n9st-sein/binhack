#include <errno.h>
#include <stdio.h>
#include <string.h>

// define FUSE_USER_VERSION before including fuse.h
#define FUSE_USE_VERSION 31
#include <fuse.h>

#define MYFS_FILE_NAME "hello"
#define MYFS_MESSAGE "Hello, Binary Hacks!"

//initialize filesystem
static void *myinit(struct fuse_conn_info *conn, struct fuse_config *cfg) {
	//Do nothing
	return NULL;
}

//getattr
//set attribute of file/directory of gaven PATH to stbuf
static int my_getattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi) {
	int res = 0;

	memset(stbuf, 0, sizeof(struct stat));
	if (strcmp(path, "/") == 0) {
		stbuf->st_mode = (S_IFDIR | 0755);
		stbuf->st_nlink = 2;
	} else if (strcmp(path + 1, MYFS_FILE_NAME) == 0) {
		//read only
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = sizeof(MYFS_MESSAGE);
	} else
		res = -ENOENT;

	return res;
}

//readdir
//set entry of directory instruct by PATH to buf
static int my_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi, enum fuse_readdir_flags flags){
	//there is no "/"directory except toplevel 
	if(strcmp(path, "/") != 0)
		return -ENOENT;

	//show ".","..","hello" in directory
	filler(buf, ".", NULL, 0, 0);
	filler(buf, "..", NULL, 0, 0);
	filler(buf, MYFS_FILE_NAME, NULL, 0, 0);
	return 0;

}
//open
//handling when open the file instructed by PATH
static int my_open(const char *path, struct fuse_file_info *fi) {
	if (strcmp(path + 1, MYFS_FILE_NAME) != 0)
		return -ENOENT;

	if ((fi->flags & O_ACCMODE) != O_RDONLY)
		return -EACCES;

	return 0;
}

//read
//fill the file indicated by PATH with buf
static int my_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi){
	//fail if try to read files except "hello"
	if (strcmp(path + 1, MYFS_FILE_NAME) != 0)
		return -ENOENT;

	//write buf "Hello, Binary Hacks"
	size_t len = sizeof(MYFS_MESSAGE);
	if (len <= offset) {
		return 0;
	}
	if (len < offset + size) {
		size = len - offset;
	}
	memcpy(buf, MYFS_MESSAGE + offset, size);

	return size;
}

static const struct fuse_operations my_fuse_ops = {
	.init = myinit,
	.getattr = my_getattr,
	.readdir = my_readdir,
	.open = my_open,
	.read = my_read,
};

int main(int argc, char *argv[]) {
	int ret;
	struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

	ret = fuse_main(args.argc, args.argv, &my_fuse_ops, NULL);
	fuse_opt_free_args(&args);

	return ret;
}
