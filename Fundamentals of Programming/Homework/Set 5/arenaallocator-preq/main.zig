const std = @import("std");
var deballoc: std.heap.DebugAllocator(.{
    .thread_safe = true,
}) = .init;

// forbidden functions
export fn malloc() callconv(.c) noreturn {
    const s = @src();
    std.debug.print(
        \\you are not allowed to use {s}
        \\you shall not pass!
    , .{s.fn_name});
    std.process.abort();
}
export fn calloc() callconv(.c) noreturn {
    const s = @src();
    std.debug.print(
        \\you are not allowed to use {s}
        \\you shall not pass!
    , .{s.fn_name});
    std.process.abort();
}
export fn realloc() callconv(.c) noreturn {
    const s = @src();
    std.debug.print(
        \\you are not allowed to use {s}
        \\you shall not pass!
    , .{s.fn_name});
    std.process.abort();
}

var max_mem: usize = 0;
var total_mem: usize = 0;
var peak_mem_used: usize = 0;
extern fn my_main() callconv(.c) void;
export fn my_alloc(len: usize) callconv(.c) [*c]u8 {
    total_mem += len;
    if (total_mem > peak_mem_used) peak_mem_used = total_mem;

    if (total_mem > max_mem) {
        std.debug.print(
            \\you've consumed too much memory ({d})
            \\you shall not pass!
        , .{total_mem});
        std.process.abort();
    }

    // std.debug.print("hello world alloc\n", .{});
    const x = deballoc.allocator()
        .rawAlloc(
        len,
        std.mem.Alignment.fromByteUnits(@alignOf(usize)),
        @returnAddress(),
    ).?;
    return x;
}
export fn my_free(ptr: [*c]u8, len: usize) callconv(.c) void {
    total_mem -= len;

    // std.debug.print("hello world free\n", .{});
    var p: []u8 = undefined;
    p.ptr = ptr;
    p.len = len;
    deballoc.allocator().rawFree(
        p,
        .fromByteUnits(@alignOf(usize)),
        @returnAddress(),
    );
}
var stdin_reader: *std.io.Reader = undefined;
var stdout_writer: *std.io.Writer = undefined;

pub fn peekWhitespace() ![]u8 {
    const r = stdin_reader;
    const buffer = r.buffer[0..r.end];
    const seek = r.seek;
    if (std.mem.indexOfAnyPos(u8, buffer, seek, std.ascii.whitespace[0..])) |end| {
        @branchHint(.likely);
        return buffer[seek .. end + 1];
    }
    // TODO take a parameter for max search length rather than relying on buffer capacity
    try r.rebase(r.buffer.len);
    while (r.buffer.len - r.end != 0) {
        const end_cap = r.buffer[r.end..];
        var writer: std.io.Writer = .fixed(end_cap);
        const n = r.vtable.stream(r, &writer, .limited(end_cap.len)) catch |err| switch (err) {
            error.WriteFailed => unreachable,
            else => |e| return e,
        };
        r.end += n;
        if (std.mem.indexOfAnyPos(u8, end_cap[0..n], 0, std.ascii.whitespace[0..])) |end| {
            return r.buffer[0 .. r.end - n + end + 1];
        }
    }
    return error.StreamTooLong;
}

export fn read_int() callconv(.c) u32 {
    while (std.mem.containsAtLeastScalar(
        u8,
        std.ascii.whitespace[0..],
        1,
        stdin_reader.peekByte() catch std.process.abort(),
    ))
        stdin_reader.toss(1);
    const buf = peekWhitespace() catch std.process.abort();
    stdin_reader.toss(buf.len);
    return std.fmt.parseInt(u32, buf[0 .. buf.len - 1], 10) catch std.process.abort();
}
export fn read_str(buf: [*c]u8, len: usize) callconv(.c) void {
    var p: []u8 = undefined;
    p.ptr = buf;
    p.len = len;
    var stream = std.io.Writer.fixed(p);
    stdin_reader.streamExact(&stream, len) catch std.process.abort();
}
export fn print_result(res: u8) callconv(.c) void {
    stdout_writer.print("{}\n", .{res}) catch std.process.abort();
    stdout_writer.flush() catch std.process.abort();
}
export fn main() void {
    var rbuf: [1 << 10]u8 = undefined;
    var wbuf: [1 << 10]u8 = undefined;
    var rdr = std.fs.File.stdin().reader(rbuf[0..]);
    var wrt = std.fs.File.stdout().writer(wbuf[0..]);
    stdin_reader = &rdr.interface;
    stdout_writer = &wrt.interface;

    max_mem = std.fmt.parseInt(
        usize,
        rdr.interface.takeDelimiterExclusive('\n') catch std.process.abort(),
        10,
    ) catch std.process.abort();
    const leak_check = std.mem.eql(
        u8,
        "true",
        rdr.interface.takeDelimiterExclusive('\n') catch std.process.abort(),
    );
    my_main();

    std.debug.print(
        \\peak memory used: {d}
        \\
    , .{peak_mem_used});

    if (leak_check and deballoc.detectLeaks()) {
        std.debug.print(
            \\you've leaked precious memory
            \\you shall not pass!
            \\
        , .{});
        std.process.abort();
    }
}
