#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/mman.h>
#endif

#include "../errors.hpp"
#include "jitcache.hpp"

JitCache::JitCache()
{
    //We reserve blocks so that they don't get reallocated.
    blocks.reserve(1024 * 4);
    current_block = nullptr;
}

//Allocate a block with read and write, but not executable, privileges.
void JitCache::alloc_block(uint32_t pc)
{
    JitBlock new_block;

    new_block.mem = nullptr;
    new_block.block_start = nullptr;
    new_block.start_pc = pc;
#ifdef _WIN32
    Errors::die("[JIT] alloc_block not implemented for WIN32");
#else
    new_block.block_start = (uint8_t*)mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif

    if (!new_block.block_start)
        Errors::die("[JIT] Unable to allocate block");

    new_block.mem = new_block.block_start;

    blocks.push_back(new_block);
    current_block = &blocks[blocks.size() - 1];
}

void JitCache::flush_all_blocks()
{
    //Deallocate all virtual memory claimed by blocks
    for (unsigned int i = 0; i < blocks.size(); i++)
    {
#ifdef _WIN32
        Errors::die("[JIT] flush_all_blocks not implemented for WIN32");
#else
        munmap(blocks[i].block_start, BLOCK_SIZE);
#endif
    }

    //Clear out the blocks vector and replace it with an empty one.
    //We reserve blocks to prevent them from getting reallocated
    blocks = std::vector<JitBlock>();
    blocks.reserve(1024 * 4);
    current_block = nullptr;
}

uint8_t* JitCache::get_current_block_start()
{
    return current_block->block_start;
}

//Replace a block's write privileges with executable privileges.
//This is to prevent the security risks that RWX memory has.
void JitCache::set_current_block_rx()
{
#ifdef _WIN32
    Errors::die("[JIT] set_current_block_rx not implemented for WIN32");
#else
    int error = mprotect(current_block->block_start, BLOCK_SIZE, PROT_READ | PROT_EXEC);
    if (error == -1)
        Errors::die("[JIT] set_current_block_rx failed");
#endif
}
