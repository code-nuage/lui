local function parse_ansi()
    local c = io.read(1)
    if c ~= "\27" then
        return c
    end

    local seq = c

    local next_char = io.read(1)
    if not next_char then return seq end
    seq = seq .. next_char

    while true do
        local ch = io.read(1)
        if not ch then break end
        seq = seq .. ch
        local byte = string.byte(ch)
        if byte >= 64 and byte <= 126 then
            -- Fin de séquence ANSI détectée
            break
        end
    end

    return seq
end


return function()
    local function restore()
        lui.graphics.clear()
        os.execute("stty sane")                                                -- Restore non-blocking
        io.write("\27[0m")                                                     -- Reset colors
        io.write("\27[?25h")                                                   -- Restore separation line
    end

    local function handler(err)
        restore()
        print(debug.traceback(err))
        io.write("Enter to exit > ")
        local input = io.read()
        return debug.traceback(err)
    end

    local function run()
        lui.graphics.clear()
        if type(lui.load) == "function" then
            lui.load()
        end
        while lui.running do
            if type(lui.draw) == "function" then
                lui.draw()
            end
            if type(lui.update) == "function" then
                lui.input = parse_ansi()
                lui.update()
            end
        end
    end

    xpcall(function()
        os.execute("stty raw -echo")                                           -- Non-blocking inputs
        io.write("\27[?25l")                                                   -- Hide separation line
        run()
    end, handler)

    restore()
end
