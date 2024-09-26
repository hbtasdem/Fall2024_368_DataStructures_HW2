#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WINDOWS 100 // Maximum number of windows that can be handled

typedef struct
{
    int id;
} Window;

Window windows[MAX_WINDOWS]; // Array to store windows
int num_windows = 0;         // Number of currently open windows

// Helper function to find the index of a window by its ID
int find_window(int id)
{
    for (int i = 0; i < num_windows; i++)
    {
        if (windows[i].id == id)
        {
            return i;
        }
    }
    return -1; // Window not found
}

// Open a new window, bring it into focus
void open_window(int id)
{
    // Shift all windows to the right to make room at the front
    for (int i = num_windows; i > 0; i--)
    {
        windows[i] = windows[i - 1];
    }
    // Add new window at the front
    windows[0].id = id;
    num_windows++;
}

// Switch focus to an existing window
void switch_window(int id)
{
    int index = find_window(id);
    if (index != -1)
    {
        // Bring selected window to the front
        Window temp = windows[index];
        for (int i = index; i > 0; i--)
        {
            windows[i] = windows[i - 1];
        }
        windows[0] = temp;
    }
}

// Close an existing window
void close_window(int id)
{
    int index = find_window(id);
    if (index != -1)
    {
        // Remove the window by shifting others to the left
        for (int i = index; i < num_windows - 1; i++)
        {
            windows[i] = windows[i + 1];
        }
        num_windows--;
    }
}

int main(void)
{
    char command[10]; // Command string
    int id;           // Window ID

    // Read input until EOF
    while (scanf("%s %d", command, &id) == 2)
    {
        if (strcmp(command, "open") == 0)
        {
            open_window(id);
        }
        else if (strcmp(command, "switch") == 0)
        {
            switch_window(id);
        }
        else if (strcmp(command, "close") == 0)
        {
            close_window(id);
        }

        // Print the ID of the currently focused window
        if (num_windows > 0)
        {
            printf("%d\n", windows[0].id);
        }
        else
        {
            // Exit if there are no windows left open
            exit(0);
        }
    }

    return 0;
}
