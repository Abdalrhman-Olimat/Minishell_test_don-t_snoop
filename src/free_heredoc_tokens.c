#include "../includes/mini.h"

// Add a node to the tracking array within the struct
void track_heredoc_node(t_heredoc_tracker *tracker, t_input *node)
{
    if (!tracker || !node)
        return;
        
    if (tracker->count < 99)
        tracker->nodes[tracker->count++] = node;
}

// Free any tracked heredoc nodes that might have been missed
void free_tracked_heredoc_nodes(t_heredoc_tracker *tracker)
{
    int i;
    
    if (!tracker || tracker->count <= 0)
        return;
        
    for (i = 0; i < tracker->count && i < 100; i++) // Ensure we don't go out of bounds
    {
        if (tracker->nodes[i])
        {
            // Check if the string exists before freeing
            // Ensure it's not a special address that shouldn't be freed
            if (tracker->nodes[i]->string && 
                tracker->nodes[i]->string != (char *)0x1 && 
                tracker->nodes[i]->string != (char *)0x2 && 
                tracker->nodes[i]->string != (char *)0x3)
            {
                free(tracker->nodes[i]->string);
            }
                
            // Free the node itself
            free(tracker->nodes[i]);
            tracker->nodes[i] = NULL;
        }
    }
    tracker->count = 0;
}
