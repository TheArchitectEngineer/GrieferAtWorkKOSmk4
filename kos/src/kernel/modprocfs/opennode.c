/* Copyright (c) 2019 Griefer@Work                                            *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODPROCFS_OPENNODE_C
#define GUARD_MODPROCFS_OPENNODE_C 1

#include <kernel/compiler.h>
#include <kernel/driver.h>

#include "procfs.h"

DECL_BEGIN

INTERN NONNULL((1, 2, 3, 4)) void KCALL
ProcFS_OpenNode(struct superblock *__restrict self,
                struct inode *__restrict node,
                struct directory_node *__restrict UNUSED(parent_directory),
                struct directory_entry *__restrict UNUSED(parent_directory_entry))
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	ino_t ino;
	uint8_t type;
	ino = node->i_fileino;
	type = (u8)(((u64)ino & PROCFS_INO_TYPEMASK) >> PROCFS_INO_TYPESHFT);
	switch (type) {

	case PROCFS_INOTYPE_SINGLETON: {
		unsigned int id;
		id = (unsigned int)((u64)ino & PROCFS_INOTYPE_SINGLETON_IDMASK);
		if (id >= PROCFS_SINGLETON_COUNT)
			goto badino;
#ifndef PROCFS_NO_CUSTOM
		if (id >= PROCFS_SINGLETON_START_CUSTOM) {
			node->i_fsdata = (struct inode_data *)ProcFS_Singleton_FsData[id];
			node->i_type   = ProcFS_Singleton_CustomTypes[id - PROCFS_SINGLETON_START_CUSTOM];
			break;
		}
#endif /* !PROCFS_NO_CUSTOM */
		node->i_fsdata = (struct inode_data *)ProcFS_Singleton_FsData[id];
		node->db_parts = VM_DATABLOCK_ANONPARTS;
		if (id >= PROCFS_SINGLETON_START_LNK_DYN)
			node->i_type = &ProcFS_Singleton_DynamicSymlink_Type;
		else if (id >= PROCFS_SINGLETON_START_REG_RO)
			node->i_type = &ProcFS_Singleton_RegularRo_Type;
		else if (id > PROCFS_SINGLETON_ROOT)
			node->i_type = &ProcFS_Singleton_Directory_Type;
		else {
			node->i_type = &ProcFS_RootDirectory_Type;
		}
	}	break;

	default:
badino:
		THROW(E_FSERROR_DELETED,
		      INODE_ISDIR(node) ? E_FILESYSTEM_DELETED_PATH
		                        : E_FILESYSTEM_DELETED_FILE);
		break;
	}
	node->i_filenlink = 0;
}


DECL_END

#endif /* !GUARD_MODPROCFS_OPENNODE_C */
