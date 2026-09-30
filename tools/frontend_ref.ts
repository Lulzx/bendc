// The official parser's answer for tools/frontend.py's parse lane: loads each
// file (and its imports) with the checkout's own bend2/bend.ts, as the CLI's
// book_read does before it validates, and prints nothing (exit 0) or the
// error the CLI would print (exit 1). Run with bun from the checkout's root:
//
//   bun <repo>/tools/frontend_ref.ts <checkout> <file>...
//
// Each answer is one JSON line {file, out}, out in frontend.py's format.
import * as path from "node:path";

const [up, ...files] = process.argv.slice(2);
const B = await import(path.resolve(up, "bend2/bend.ts"));

function show(e: unknown): string {
  if (e instanceof RangeError) {
    return "Error: the machine stack overflowed (a deep recursion, or a"
      + " literal too large to expand)";
  }
  const err = e as { $?: string };
  return err?.$ === "Err" ? B.err_show(err) : String(e);
}

for (const file of files) {
  let out: string;
  try {
    await B.book_load(B.book_nil(), file, "", new Map());
    out = "\nexit 0\n";
  } catch (e) {
    const text = ("SOME PROOFS FAIL\n" + show(e)).replace(/[ \t]+$/gm, "").trimEnd();
    out = text + "\nexit 1\n";
  }
  console.log(JSON.stringify({ file, out }));
}
