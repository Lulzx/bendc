function hub_ensure(lib, hub, rel) {
  const fs = require("fs");
  const path = require("path");
  const crypto = require("crypto");
  const cp = require("child_process");
  if (fs.existsSync(lib + "/" + rel)) {
    return io_done({ $: "Unit" });
  }
  const pkg = rel.split("/")[0];
  const get = (sub, hash) => {
    let src = null;
    try {
      src = cp.execFileSync("curl", ["-fsSL", "--max-time", "60", hub + "/" + sub]).toString("utf8");
    } catch {}
    const sum = src === null ? "" : crypto.createHash("sha256").update(src).digest("hex");
    if (src === null || hash.length < 32 || !sum.startsWith(hash) || path.posix.normalize("/" + sub) !== "/" + sub) {
      throw "expected a file at " + hub + "/" + sub + " hashing to " + hash;
    }
    return src;
  };
  try {
    const man = get(pkg + "/manifest", pkg.slice(2));
    for (const line of man.trim().split("\n")) {
      const [h, p] = line.split(" ");
      const src = get(pkg + "/" + p, h);
      const at = lib + "/" + pkg + "/" + p;
      fs.mkdirSync(path.dirname(at), { recursive: true });
      fs.writeFileSync(at, src);
    }
  } catch (e) {
    return { $: "Fail", error: io_tup(1, String(e)) };
  }
  return io_done({ $: "Unit" });
}
