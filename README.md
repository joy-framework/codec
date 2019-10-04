# codec

base64 encode/decode library for janet

## Install

Add to your `project.janet` file

```clojure
{:dependencies [{:repo "https://github.com/joy-framework/codec" :tag ""}]}
```

## Use

```clojure
(import codec)

(= "hello there!" (codec/decode (codec/encode "hello there!")))
```

And that's all folks
