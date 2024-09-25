#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WINDOWS 100 // You can adjust this as needed

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
int open_window(int id)
{
    // Shift all windows to the right to make room at the front
    for (int i = num_windows; i > 0; i--)
    {
        windows[i] = windows[i - 1];
    }

    // Add new window at the front
    windows[0].id = id;
    num_windows++;

    // Return the ID of the currently focused window
    return windows[0].id;
}

// Switch focus to an existing window
int switch_window(int id)
{
    int index = find_window(id);

    if (index != -1)
    {
        // Shift all windows to the right, bring selected window to front
        Window temp = windows[index];
        for (int i = index; i > 0; i--)
        {
            windows[i] = windows[i - 1];
        }
        windows[0] = temp;

        // Return the ID of the currently focused window
        return windows[0].id;
    }
    return -1; // If switch failed
}

// Close an existing window
int close_window(int id)
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

        // If there are no windows left, terminate
        if (num_windows == 0)
        {
            exit(0);
        }

        // Return the ID of the currently focused window
        return windows[0].id;
    }
    return -1; // If close failed
}

int main(void)
{
    char command[10];
    int id;

    // Read input until EOF
    while (scanf("%s %d", command, &id) == 2)
    {
        int focused_id = -1; // To hold the ID of the currently focused window
        if (strcmp(command, "open") == 0)
        {
            focused_id = open_window(id);
        }
        else if (strcmp(command, "switch") == 0)
        {
            focused_id = switch_window(id);
        }
        else if (strcmp(command, "close") == 0)
        {
            focused_id = close_window(id);
        }

        // Print the ID of the currently focused window
        if (focused_id != -1)
        {
            printf("%d\n", focused_id);
        }
    }

    return 0;
}
