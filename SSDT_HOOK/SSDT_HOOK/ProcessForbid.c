
/*
 * @author Yue 
 *
 */

#include "ProcessForbid.h"

extern LIST_ENTRY ForbidProcessList;

extern KSPIN_LOCK ForbidProcessListLock;

//²åÈëÖ¸¶¨½ø³ÌÃû½øÈë½ø³Ì½ø³ÌÁ´
BOOLEAN InsertForbidProcessList(PForbidProcess pFP){
	BOOLEAN inserted = FALSE;
	KLOCK_QUEUE_HANDLE handle;
	KeAcquireInStackQueuedSpinLock(&ForbidProcessListLock, &handle);

	InsertHeadList(&ForbidProcessList, &pFP->listEntry);
	inserted = TRUE;

	KeReleaseInStackQueuedSpinLock(&handle);
	return inserted;
}

//ÒÆ³ýÖ¸¶¨½ø³ÌÃû
BOOLEAN RemoveForbidProcessList(PForbidProcess pFP){
	BOOLEAN removed = FALSE;
	KLOCK_QUEUE_HANDLE handle;
	KeAcquireInStackQueuedSpinLock(&ForbidProcessListLock, &handle);

	RemoveEntryList(&pFP->listEntry);
	removed = TRUE;

	KeReleaseInStackQueuedSpinLock(&handle);
	return removed;
}
