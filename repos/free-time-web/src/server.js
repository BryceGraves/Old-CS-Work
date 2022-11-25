const app = require("express")();
const stripe = require("stripe")("sk_test_gCFR5VFBfr6ggX0vFtx2autt00QgvGOcUU");

app.use(require("body-parser").text());

app.post("/charge", async (req, res) => {
  try {
    let { status } = await stripe.charges.create({
      amount: 2000,
      currency: "usd",
      description: "An example charge",
      source: req.body
    });

    res.json({ status });
  } catch (err) {
    console.log(err);
    res.status(500).end();
  }
});

let port = process.env.PORT;
if (port == null || port == "") {
  port = 9000;
}

app.listen(port, () => console.log("Listening on port " + port));