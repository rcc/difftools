/*
 * difftools.c - various diff formatting tools.
 *
 * Copyright (C) 2010 Robert C. Curtis
 *
 * difftools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * difftools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with difftools.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <prjutil.h>
#include <cmds.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

int main(int argc, const char * argv[])
{
	int ret;
	int status = 0;
	char *cmdname;
	char *arg0;

	/* create the command string */
	if((arg0 = malloc(strlen(argv[0]))) == NULL) {
		perror("Could not allocate arg0");
		status = -1;
		goto exit;
	}
	strcpy(arg0, argv[0]);
	if((cmdname = basename(arg0)) == NULL) {
		perror("Could not get basename of command");
		status = -1;
		goto exit;
	}

	pdebug("Command: %s\n", cmdname);
	pdebug("Version: %s\n", SCM_HASH);

	if(strcmp("difftools", cmdname) == 0) {
		if((ret = run_cmds(argc-1, &argv[1], NULL)) < 0) {
			fprintf(stderr,
				"An error occurred with command at position "
				"%d\n", -ret);
			status = -1;
			goto exit;
		}
	} else {
		/* treat the argv[0] command name as a command */
		status = run_cmd(cmdname, argc - 1, &argv[1], NULL);
		if(status != 0)
			fprintf(stderr,
				"An error occurred with command: %s\n",
				cmdname);
	}

exit:
	return status;
}

CMDHANDLER(version)
{
	printf("Version: %s\n", SCM_HASH);
	return 0;
}
APPCMD(version, &version, "print the version", "usage: version", NULL);
