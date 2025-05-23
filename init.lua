local base = (...):gsub("init", "")

_G.lui = {}

lui.running = true

function lui.exit()
    lui.running = false
end

lui.run = require(base .. "run")
lui.graphics = require(base .. "graphics")
lui.colors = require(base .. "colors")
lui.keyboard = require(base .. "keyboard")
lui.keys = require(base .. "keys")

return lui