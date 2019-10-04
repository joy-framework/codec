(import tester :prefix "" :exit true)
(import build/codec :as codec)

(deftest
  (test "a base64 encoded then decoded string is the same as the original"
    (let [str "original string"]
      (= str (codec/decode
               (codec/encode str))))))
