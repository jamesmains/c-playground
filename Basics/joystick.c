#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>

// Read joystick events from /dev/input/js1 and print them to the console
int main(){
    int fd = open("/dev/input/js1", O_RDONLY);
    if (fd == -1){
        perror("Could not open joystick device");
        return 1;
    }

    struct js_event event;

    while(read(fd, &event, sizeof(event)) > 0){
        if (event.type & JS_EVENT_BUTTON){
            printf("Button %u %s\n", event.number, event.value ? "pressed" : "released");
        } else if (event.type & JS_EVENT_AXIS){
            printf("Axis %u moved to %d\n", event.number, event.value);
        }
    }
    close(fd);

    return 0;   
}