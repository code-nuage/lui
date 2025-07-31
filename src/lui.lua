local lui = {}

lui.stop = function()
    lui.STATE = false
end

lui.STATE = true
lui.graphics = require("lui.graphics")
lui.keyboard = require("lui.keyboard")

lui.run = function() require("lui.run")(lui) end

return lui