
----------------------------------------------------
function setup()

end

----------------------------------------------------
function draw()

    lvg.clear()

    lvg.strokeWidth( 0.05 )
    lvg.setCapRound() -- butt / round / square
    lvg.setJoinMiter() --miter / round / bevel 

    lvg.center()
    
    lvg.stroke()    
    local offset = 0.1
    local side = 0.05
    lvg.begin()
        --lvg.poly( 0.0, 0.0, 0.15 + offset*3, 4 )
    lvg.close()

    for i=1,3 do 
        local m0 = lfo.triangle( 0.13 + i*0.019 )
        lvg.stroke( 1.0, m0*m0 )
        lvg.begin()
            lvg.poly( 0.0, offset*i,  side, 4 )
            lvg.poly( 0.0, -offset*i, side, 4 )
        lvg.close()
        
        local m1 = lfo.triangle( 0.2 + i*0.017 ) 
        lvg.stroke( 1.0, m1*m1 )
        lvg.begin()
            lvg.poly( offset*i, 0.0, side, 4 )
            lvg.poly( -offset*i, 0.0, side, 4 )
        lvg.close()
    end

end

----------------------------------------------------
function exit()

end


