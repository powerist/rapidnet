(set-logic S)
(declare-fun variable177 () String)
(declare-fun variable178 () String)
(declare-fun variable179 () String)
(declare-fun variable184 () String)
(declare-fun variable185 () String)
(declare-fun variable186 () String)
(declare-fun variable187 () String)
(declare-fun variable188 () String)
(declare-fun variable189 () String)
(declare-fun variable190 () String)
(declare-fun variable191 () String)
(declare-fun variable192 () String)
(declare-fun variable204 () String)
(declare-fun variable205 () String)
(declare-fun variable261 () String)
(declare-fun variable262 () String)
(declare-fun variable264 () String)
(declare-fun variable265 () String)
(declare-fun variable266 () String)
(declare-fun variable267 () String)
(declare-fun variable268 () String)
(declare-fun variable269 () String)
(declare-fun variable270 () String)
(declare-fun variable271 () String)
(declare-fun variable272 () String)
(declare-fun variable273 () String)
(declare-fun variable274 () String)
(declare-fun variable275 () String)
(declare-fun variable276 () String)
(declare-fun f_prepend (String String ) String)
(assert(= variable272 variable261))
(assert(= variable273 variable262))
(assert(= variable274 variable264))
(assert(= variable272 variable204))
(assert(= variable271 variable205))
(assert(= variable271 variable178))
(assert(= variable274 variable179))
(assert(= variable177 (f_prepend variable178 variable179 )))
(assert(= variable272 variable267))
(assert(= variable268 variable184))
(assert(= variable273 variable185))
(assert(= variable177 variable186))
(assert(= variable184 (f_prepend variable185 variable186 )))
(assert(= variable275 variable187))
(assert(= variable270 variable188))
(assert(= variable265 variable189))
(assert(= variable187 (f_prepend variable188 variable189 )))
(assert(= variable276 variable190))
(assert(= variable269 variable191))
(assert(= variable266 variable192))
(assert(= variable190 (f_prepend variable191 variable192 )))
(check-sat)
