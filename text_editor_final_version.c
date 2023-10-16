#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define buffer_size_limit 1000
#define word_size_limit 50

char buffer[buffer_size_limit] = {0};

void enter_the_text() 
{
    char entered_text[buffer_size_limit];
    int left_space;
	
	printf("\n");
    printf("Enter the text: \n");

    fgets(entered_text, buffer_size_limit, stdin);

    left_space = buffer_size_limit - strlen(buffer) - 1;

    strncat(buffer, entered_text, left_space); 
    
	printf("\n");
    printf("The updated text:\n%s\n", buffer);
}

int separated_word(char c) 
{
    return isspace(c) || ispunct(c) || c == '\0';
}

int word_search(char* word) 
{
    int counter = 0;
    char* current_position = buffer;

    while (current_position != NULL) 
	{
        current_position = strstr(current_position, word);
        
        if (current_position != NULL) 
		{
            char before, after;

            if (current_position == buffer) 
			{
                before = ' ';
            } 
			else 
			{
                before = *(current_position - 1);
            }

            after = *(current_position + strlen(word));

            if (separated_word(before) && separated_word(after)) 
			{
                counter++;
            }
            current_position = current_position + strlen(word);
        }
    }
    return counter;
}

void word_replacement(char* word, char* substitute) 
{
    char temp_buffer[buffer_size_limit];
    char *pos = buffer;
    char *last_pos = buffer;
    char *current_pos_in_temp = temp_buffer;

    int word_length = strlen(word);
    int substitute_length = strlen(substitute);

    memset(temp_buffer, 0, buffer_size_limit);

    while ((pos = strstr(pos, word)) != NULL) 
    {
        int copy_length = pos - last_pos;
        
        strncpy(current_pos_in_temp, last_pos, copy_length);
        current_pos_in_temp = current_pos_in_temp + copy_length;

        strcpy(current_pos_in_temp, substitute);
        current_pos_in_temp = current_pos_in_temp + substitute_length;

        pos = pos + word_length;
        last_pos = pos;
    }

    strcpy(current_pos_in_temp, last_pos);
    strcpy(buffer, temp_buffer);

    printf("\n");
    printf("The updated text:\n%s\n", buffer);
}

void delete_buffer() 
{
    buffer[0] = '\0';
    printf("The content from buffer was deleted\n");
}

int main () 
{
    char word[word_size_limit], substitute[word_size_limit];
    int choice;
    
    printf("\nMenu:\n");
    printf("1) Enter Text\n");
    printf("2) Search for Word\n");
    printf("3) Replace Word\n");
    printf("4) Delete\n");
    printf("5) Exit\n");

    while (1) 
	{
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();
      
        switch (choice) 
		{
            case 1:
                enter_the_text();
                break;
            case 2:
                printf("Enter the word for searching:\n");
                scanf("%s", word);
                printf("\nNumber of occurrences: %d\n", word_search(word));
                break;
            case 3:
                printf("\nEnter the word for replacement:\n");
                scanf("%s", word);
                printf("\nEnter the replacement:\n");
                scanf("%s", substitute);
                word_replacement(word, substitute);
                break;
            case 4:
                delete_buffer();
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}
