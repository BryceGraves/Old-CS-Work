const app = require("express")();
const stripe = require("stripe")("sk_test_gCFR5VFBfr6ggX0vFtx2autt00QgvGOcUU");
const cors = require('cors')

app.use(require("body-parser").text());
app.use(cors());

app.post("/charge", async (req, res) => {
  try {
    let data = JSON.parse(req.body);
    let { status } = await stripe.charges.create({
      amount: data.amount,
      currency: "usd",
      description: data.description,
      source: data.source
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