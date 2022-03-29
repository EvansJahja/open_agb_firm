/*
 *   This file is part of open_agb_firm
 *   Copyright (C) 2021 derrek, profi200
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "types.h"
#include "error_codes.h"
#include "drivers/gfx.h"
#ifdef ARM11
	#include "arm11/fmt.h"
	#include "arm11/drivers/hid.h"
#endif



#ifdef ARM11
void printError(Result res)
{
	static const char *const common[] =
	{
		"OK",
		"SD card removed",
		"Disk full",
		"Invalid argument",
		"Out of memory",
		"Out of range",
		"Not found",
		"Path too long",

		// fatfs errors.
		"fatfs disk error",
		"fatfs assertion failed",
		"fatfs disk not ready",
		"fatfs file not found",
		"fatfs path not found",
		"fatfs invalid path name",
		"fatfs access denied",
		"fatfs already exists",
		"fatfs invalid file/directory object",
		"fatfs drive write protected",
		"fatfs invalid drive",
		"fatfs drive not mounted",
		"fatfs no filesystem",
		"fatfs f_mkfs() aborted",
		"fatfs thread lock timeout",
		"fatfs file locked",
		"fatfs not enough memory",
		"fatfs too many open objects",
		"fatfs invalid parameter"
	};
	static const char *const custom[] =
	{
		"ROM too big. Max 32 MiB",
		"Failed to set GBA RTC"
	};

	if(res < CUSTOM_ERR_OFFSET) ee_printf("Error: %s.\n", common[res]);
	else
	{
		ee_printf("Error: %s.\n", custom[res - CUSTOM_ERR_OFFSET]);
	}
}

void printErrorWaitInput(Result res, u32 waitKeys)
{
	printError(res);

	do
	{
		GFX_waitForVBlank0();

		hidScanInput();

		if(hidKeysDown() & waitKeys) break;
		if(hidGetExtraKeys(KEY_POWER) & KEY_POWER) break;
	} while(1);
}
#endif // ifdef ARM11