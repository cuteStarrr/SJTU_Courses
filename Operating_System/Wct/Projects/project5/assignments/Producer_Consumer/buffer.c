# include "buffer.h"

// circular queue to maintain a buffer
buffer_item buffer[BUFFER_SIZE + 1];
int head, tail;

// insert an item to the buffer
int insert_item(buffer_item item) {
	if ((tail + 1) % (BUFFER_SIZE + 1) == head) return -1;
	tail = (tail + 1) % (BUFFER_SIZE + 1);
	buffer[tail] = item;
	return 0;
}

// remove an item from the buffer
int remove_item(buffer_item *item) {
	if (head == tail) return -1;
	head = (head + 1) % (BUFFER_SIZE + 1);
	*item = buffer[head];
	return 0;
}

void buffer_initialization() {
	head = 0; 
	tail = 0;
}
