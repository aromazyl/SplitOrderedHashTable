#pragma once

#define atomic_load(p) ({typeof(*(p)) __tmp= *(p); load_barrier(); __tmp;})
#define atomic_store(p,v) do { store_barrier(); *(p) = v; } while (0);
