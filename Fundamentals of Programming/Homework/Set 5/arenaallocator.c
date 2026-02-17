extern char *my_alloc(unsigned long len);
extern void my_free(char *ptr, unsigned long len);
extern unsigned read_int();
extern void read_str(char *buf, unsigned long len);
extern void print_result(unsigned char res);

#define FIRST_BLOCK_SIZE (1 << 6)
#define BLOCK_COUNT 20
// |block[i]| == (FIRST_BLOCK_SIZE << i)

typedef struct { // suggested layout
    char *backing_buffer;
    unsigned long buffer_len;
    unsigned long allocated;
} ArenaBlock;
void arena_block_init(ArenaBlock *block) {
    block->backing_buffer = 0;
    block->buffer_len = 0;
    block->allocated = 0;
}
void arena_block_create(ArenaBlock *block, unsigned long len) {
    block->backing_buffer = my_alloc(len);
    block->buffer_len = len;
    block->allocated = 0;
}
char *arena_block_allocate(ArenaBlock *block, unsigned long len) {
    if(!block->backing_buffer || block->allocated + len > block->buffer_len) return 0;

    char *ptr = block->backing_buffer + block->allocated;
    block->allocated += len;
    return ptr;
}
void arena_block_destroy(ArenaBlock *block) {
    my_free(block->backing_buffer, block->buffer_len);
    arena_block_init(block);
}
typedef struct { // suggested layout
    ArenaBlock blocks[BLOCK_COUNT];
} ArenaAllocator;
void arena_init(ArenaAllocator *arena) {
    for(int i = 0; i < BLOCK_COUNT; i++) arena_block_init(&arena->blocks[i]);
}
void arena_destroy(ArenaAllocator *arena) {
    for(int i = 0; i < BLOCK_COUNT; i++) if(arena->blocks[i].backing_buffer) arena_block_destroy(&arena->blocks[i]);
}
char *arena_allocate(ArenaAllocator *arena, unsigned long len) {
  for (int i = 0; i < BLOCK_COUNT; ++i) {
    if (len > (FIRST_BLOCK_SIZE << i)) continue;
    if (arena->blocks[i].backing_buffer == 0) arena_block_create(&arena->blocks[i], FIRST_BLOCK_SIZE << i);
    char *ptr;
    if (!(ptr = arena_block_allocate(&arena->blocks[i], len))) continue;
    return ptr;
  }
  return 0;
}

void my_main() {
    ArenaAllocator root_arena;
    arena_init(&root_arena);
    unsigned int q = read_int();
    unsigned char** Arr = (unsigned char**)arena_allocate(&root_arena, sizeof(char *) * q);
    unsigned int* Arr_len = (unsigned int*)arena_allocate(&root_arena, sizeof(unsigned) * q);
    for(int i = 0; i < q; i++){Arr[i] = 0; Arr_len[i] = 0;}

    for (unsigned i = 0; i < q; i++) {
        if (read_int() == 1){
            // type 1: 1 n s
            ArenaAllocator scope_1;
            arena_init(&scope_1);
            int n = read_int();
            char *s = arena_allocate(&scope_1, n + 1);
            read_str(s, n);
            unsigned char hash = 0;
            for (unsigned int j = 0; j < n; ++j) {
                unsigned char c = (unsigned char)s[j];
                hash = (unsigned char)(((hash ^ c) * c) % 256);
            }
            int sb = (n + 15) / 16;
            Arr[i] = (unsigned char *)arena_allocate(&root_arena,
                                                            sizeof(unsigned char) * sb);
            Arr_len[i] = sb;
            for (unsigned int k = 0; k < sb; k++) {
                Arr[i][k] = hash;
                for (unsigned int j = k * 16; j < 16 * (k + 1) && j < n; j++)
                Arr[i][k] ^= (unsigned char)s[k];
            }
            arena_destroy(&scope_1);
        }       
        else{
            // type 2: 2 a b
            unsigned a = read_int();
            unsigned b = read_int();

            unsigned char hash = 0;
            unsigned i1 = 0, i2 = 0;
            unsigned n1 = Arr_len[a], n2 = Arr_len[b];

            while (i1 < n1 && i2 < n2) {
                hash = (hash ^ Arr[a][i1]) * Arr[a][i1] % 256;
                hash = (hash ^ Arr[b][i2]) * Arr[b][i2] % 256;
                i1++; i2++;
            }
            while (i1 < n1) { hash = (hash ^ Arr[a][i1]) * Arr[a][i1] % 256; i1++; }
            while (i2 < n2) { hash = (hash ^ Arr[b][i2]) * Arr[b][i2] % 256; i2++; }

            print_result(hash);
        }
    }

    arena_destroy(&root_arena);
}
