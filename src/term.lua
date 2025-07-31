local termio = require("posix.termio")
local unistd = require("posix.unistd")
local fcntl = require("posix.fcntl")
local bit = require("bit")

local term = {}

local CSI = "\27["

term.get_size = function()
    local ws, _ = termio.tcgetwinsize(unistd.STDIN_FILENO)
    if ws then
        return ws.ws_col, ws.ws_row
    end
end

term.clear = function()
    io.write(CSI .. "2J" .. CSI .. "H")
end

term.hide_cursor = function()
    io.write(CSI .. "?25l")
end

term.show_cursor = function()
    io.write("\27[?25h")
end

term.move_cursor = function(x, y)
    io.write(string.format(CSI .. "%d;%dH", y, x))
end

term.save_state = function()
    local state, err = termio.tcgetattr(unistd.STDIN_FILENO)

    if state then
        return state
    end
    return false, err
end

term.restore_state = function(state)
    termio.tcsetattr(unistd.STDIN_FILENO, termio.TCSANOW, state)
end

term.active_raw_mode = function()
    local fd = unistd.STDIN_FILENO

    local raw = termio.tcgetattr(fd)

    raw.lflag = bit.band(raw.lflag, bit.bnot(termio.ICANON + termio.ECHO))

    raw.iflag = bit.band(raw.iflag, bit.bnot(termio.IXON + termio.ICRNL + termio.BRKINT))

    raw.oflag = bit.band(raw.oflag, bit.bnot(termio.OPOST))

    raw.cc[termio.VMIN] = 1
    raw.cc[termio.VTIME] = 0

    termio.tcsetattr(fd, termio.TCSANOW, raw)
end

term.set_nonblocking = function()
    local fd = unistd.STDIN_FILENO

    local flags = fcntl.fcntl(fd, fcntl.F_GETFL)
    fcntl.fcntl(fd, fcntl.F_SETFL, bit.bor(flags, fcntl.O_NONBLOCK))
end

return term