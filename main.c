//
//  main.c
//  AutoRemoveDepthFile
//
//  Created by Daniel on 3/28/15.
//  Copyright (c) 2015 Daniel. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>


char *_fmt = "find ./* -name %s", *_fmt2 = "rm -rf %s";

int main(int argc, const char * argv[]) 
{
    printf("file='%s'\n", argv[1]);
    
    if (argc <= 1)
        return -1;
    
    int size = strlen(argv[1])+strlen(_fmt)+1;
    char *cmd_find = (char *)malloc(size), *cmd_rm=NULL;
    
    memset(cmd_find, 0, size);
    
    sprintf(cmd_find, _fmt, argv[1]);
    
    FILE *fp;
    
    if (fp = popen(cmd_find, "r"))
    {
        char buf[128];
        
        while (fgets(buf, sizeof(buf), fp) != NULL)
        {
            buf[strlen(buf)-1]='\0';
            //printf("'%s'\n", buf);
            
            cmd_rm = malloc(strlen(buf)+strlen(_fmt2));
            memset(cmd_rm, 0, (strlen(buf)+strlen(_fmt2)));
            sprintf(cmd_rm, _fmt2, buf);
            //printf("'%s'\n", cmd_rm);
            system(cmd_rm);
            free(cmd_rm);
        }
        pclose(fp);
    }
    
    free(cmd_find);
    
    return 0;
}
