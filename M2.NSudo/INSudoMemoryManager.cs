using System;
using System.Runtime.InteropServices;

namespace M2.NSudo
{
    /// <summary>
    /// NSudo Shared Library Memory Manager Interface V1
    /// </summary>
    [Guid("B4A4FB65-3E5C-4645-9DB0-2DE76AF7E5AC")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface INSudoMemoryManager
    {
        /// <summary>
        /// Allocates a block of memory from the default heap of the calling 
        /// process. The allocated memory will be initialized to zero. The 
        /// allocated memory is not movable.
        /// </summary>
        /// <param name="Size">
        /// The number of bytes to be allocated.
        /// </param>
        /// <returns>
        /// A pointer to the allocated memory block.
        /// </returns>
        public IntPtr AllocMemory(
            int Size);

        /// <summary>
        /// Reallocates a block of memory from the default heap of the calling 
        /// process. If the reallocation request is for a larger size, the 
        /// additional region of memory beyond the original size be initialized
        /// to zero. This function enables you to resize a memory block and 
        /// change other memory block properties.The allocated memory is not 
        /// movable.
        /// </summary>
        /// <param name="OldBlock">
        /// A pointer to the block of memory that the function reallocates. 
        /// This pointer is returned by an earlier call to the AllocMemory or 
        /// ReAllocMemory method.
        /// </param>
        /// <param name="NewSize">
        /// The new size of the memory block, in bytes. A memory block's size 
        /// can be increased or decreased by using this function.
        /// </param>
        /// <returns>
        /// A pointer to the allocated memory block. If the function fails, the
        /// original memory is not freed, and the original handle and pointer 
        /// are still valid.
        /// </returns>
        public IntPtr ReAllocMemory(
            IntPtr OldBlock,
            int NewSize);

        /// <summary>
        /// Frees a memory block allocated from a heap by the AllocMemory or 
        /// ReAllocMemory method.
        /// </summary>
        /// <param name="Block">
        /// A pointer to the memory block to be freed. This pointer is returned
        /// by the AllocMemory or ReAllocMemory method. If this pointer is 
        /// nullptr, the behavior is undefined.
        /// </param>
        public void FreeMemory(
            IntPtr Block);
    }
}
