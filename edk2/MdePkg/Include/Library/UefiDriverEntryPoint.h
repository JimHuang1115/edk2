/** @file
  Module entry point library for UEFI drivers, DXE Drivers, DXE Runtime Drivers,
  and DXE SMM Drivers.

Copyright (c) 2006 - 2008, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __MODULE_ENTRY_POINT_H__
#define __MODULE_ENTRY_POINT_H__

///
///Declare the PI Specification Revision that this driver requires to execute correctly.
///
extern CONST UINT32                   _gDxeRevision;

///
/// Declare the EFI/UEFI Specification Revision to which this driver is implemented 
///
extern CONST UINT32                   _gUefiDriverRevision;

///
/// Declare the number of unload handler in the image. 
///
extern CONST UINT8                    _gDriverUnloadImageCount;


/**
  The entry point of PE/COFF Image for a DXE Driver, DXE Runtime Driver, DXE SMM Driver, or UEFI Driver. 

  This function is the entry point for a DXE Driver, DXE Runtime Driver, DXE SMM Driver,
  or UEFI Driver.  This function must call ProcessLibraryConstructorList() and
  ProcessModuleEntryPointList(). If the return status from ProcessModuleEntryPointList()
  is an error status, then ProcessLibraryDestructorList() must be called. The return value
  from ProcessModuleEntryPointList() is returned. If _gDriverUnloadImageCount is greater
  than zero, then an unload handler must be registered for this image and the unload handler
  must invoke ProcessModuleUnloadList().
  If _gUefiDriverRevision is not zero and SystemTable->Hdr.Revision is less than _gUefiDriverRevison,
  then return EFI_INCOMPATIBLE_VERSION.


  @param  ImageHandle  ImageHandle of the loaded driver.
  @param  SystemTable  Pointer to the EFI System Table.

  @retval  EFI_SUCCESS               The DXE Driver, DXE Runtime Driver, DXE SMM Driver,
                                     or UEFI Driver exited normally.
  @retval  EFI_INCOMPATIBLE_VERSION  _gUefiDriverRevision is greater than SystemTable->Hdr.Revision.
  @retval  Other                     Return value from ProcessModuleEntryPointList().

**/
EFI_STATUS
EFIAPI
_ModuleEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );


/**
  Required by the EBC compiler and identical in functionality to _ModuleEntryPoint(). 

  This function is required to call _ModuleEntryPoint() passing in ImageHandle, and SystemTable.

  @param  ImageHandle ImageHandle of the loaded driver.
  @param  SystemTable Pointer to the EFI System Table.

  @retval  EFI_SUCCESS               The DXE Driver, DXE Runtime Driver, DXE SMM Driver,
                                     or UEFI Driver exited normally.
  @retval  EFI_INCOMPATIBLE_VERSION  _gUefiDriverRevision is greater than SystemTable->Hdr.Revision.
  @retval  Other                     Return value from ProcessModuleEntryPointList().
**/
EFI_STATUS
EFIAPI
EfiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );


/**
  Invokes the library destructors fror all dependent libraries and terminates the
  DXE Driver, DXE Runtime Driver, DXE SMM Driver, or UEFI Driver. 

  This function calls ProcessLibraryDestructorList() and the EFI Boot Service Exit()
  with a status specified by Status.

  @param  Status Status returned by the driver that is exiting.

**/
VOID
EFIAPI
ExitDriver (
  IN EFI_STATUS  Status
  );


/**
  Autogenerated function that calls the library constructors for all of the module's
  dependent libraries.

  This function must be called by _ModuleEntryPoint().
  This function calls the set of library constructors for the set of library instances
  that a module depends on.  This includes library instances that a module depends on
  directly and library instances that a module depends on indirectly through other libraries.  
  This function is autogenerated by build tools and those build tools are responsible
  for collecting the set of library instances, determine which ones have constructors,
  and calling the library constructors in the proper order based upon each of the library
  instances own dependencies.

  @param  ImageHandle ImageHandle of the loaded driver.
  @param  SystemTable Pointer to the EFI System Table.

**/
VOID
EFIAPI
ProcessLibraryConstructorList (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );


/**
  Autogenerated function that calls the library descructors for all of the module's
  dependent libraries.

  This function may be called by _ModuleEntryPoint() or ExitDriver().
  This function calls the set of library destructors for the set of library instances
  that a module depends on. This includes library instances that a module depends on
  directly and library instances that a module depends on indirectly through other libraries.  
  This function is autogenerated by build tools and those build tools are responsible for
  collecting the set of library instances, determine which ones have destructors, and calling
  the library destructors in the proper order based upon each of the library instances own dependencies.

  @param  ImageHandle ImageHandle of the loaded driver.
  @param  SystemTable Pointer to the EFI System Table.

**/
VOID
EFIAPI
ProcessLibraryDestructorList (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );


/**
  Autogenerated function that calls a set of module entry points.

  This function must be called by _ModuleEntryPoint().
  This function calls the set of module entry points.  
  This function is autogenerated by build tools and those build tools are responsible
  for collecting the module entry points and calling them in a specified order.

  @param  ImageHandle ImageHandle of the loaded driver.
  @param  SystemTable Pointer to the EFI System Table.

  @retval  EFI_SUCCESS   The UEFI Application executed normally.
  @retval  !EFI_SUCCESS  The UEFI Application failed to execute normally.
**/
EFI_STATUS
EFIAPI
ProcessModuleEntryPointList (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );


/**
  Autogenerated function that calls a set of module unload handlers.

  This function must be called from the unload handler registered by _ModuleEntryPoint().
  This function calls the set of module unload handlers.  
  This function is autogenerated by build tools and those build tools are responsible
  for collecting the module unload handlers and calling them in a specified order.

  @param  ImageHandle ImageHandle of the loaded driver.

  @retval  EFI_SUCCESS  The unoad handlers executed normally.
  @retval  !EFI_SUCCESS The unload handlers failed to execute normally.

**/
EFI_STATUS
EFIAPI
ProcessModuleUnloadList (
  IN EFI_HANDLE  ImageHandle
  );

#endif
