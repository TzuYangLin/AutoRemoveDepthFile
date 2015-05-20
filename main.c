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

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("argv[1]='%s'\n", argv[1]);
    
    if (argc <= 1)
        return -1;
    
    int size = strlen(argv[1])+strlen(_fmt)+1;
    char *cmd = (char *)malloc(size), *cmd2=NULL;
    
    memset(cmd, 0, size);
    
    sprintf(cmd, _fmt, argv[1]);
    
    FILE *fp;
    
    if (fp = popen(cmd, "r"))
    {
        char buf[128];
        
        while (fgets(buf, sizeof(buf), fp) != NULL)
        {
            buf[strlen(buf)-1]='\0';
            //printf("'%s'\n", buf);
            
            cmd2 = malloc(strlen(buf)+strlen(_fmt2));
            memset(cmd2, 0, (strlen(buf)+strlen(_fmt2)));
            sprintf(cmd2, _fmt2, buf);
            printf("'%s'\n", cmd2);
            system(cmd2);
            free(cmd2);
        }
        pclose(fp);
    }
    
    free(cmd);
    
    return 0;
}
